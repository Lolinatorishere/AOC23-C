#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define snif(STRING1 , STRING2 , RESULT) \
    if(STRING1 != STRING2){\
        RESULT;\
    }
#define isasciinum(STRING)\
    if(STRING >= 48 && STRING <= 57)

struct coords{
    char symbol;
    int x;
    int y;
};

typedef struct coords coords;

int CSV_Size(char *file_dir , int *ret_height , int *ret_length){
    FILE  *CSV_IN;
    char buffer[1024];
    int i = 0
       ,j = 0;
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 1024 , CSV_IN)){
        i++;
        }
        while(buffer[j] != '\0'){
        j++; 
        }
    *ret_height = i;
    *ret_length = j;
    }
    return 0;
}

int CSV_Input(char *file_dir , char *grid[] , int g_height , int g_length){
    FILE  *CSV_IN;
    int i = 0
       ,j = 0 
       ,values = 0;
    char buffer[1024];
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while (i < g_height){
            fgets(buffer , 1024 , CSV_IN);
            for(j = 0 ; j < g_length ; j++){
                grid[i][j] = buffer[j];
            }
            i++;
        }
    }
    fclose(CSV_IN);
    return 0;
}

void Symbol_Finder(char *string , int string_length , int y_pos , coords *symbol_pos , int *symbol_total){
    int i = 0
       ,j = *symbol_total;
    for(i = 0 ; i < string_length ; i++){
        if(string[i] != '.' && (string[i] < 48 || string[i] > 57)){
            symbol_pos[j].x = i;
            symbol_pos[j].y = y_pos; 
            symbol_pos[j].symbol = string[i];
            j++;
        }
    }
    *symbol_total = j;
}

int String_Wipe(char *string , int s_length){
    if(string == NULL){
        return 1;
    }
    for(int i = 0 ; i < s_length ; i++){
        string[i] = '\0';
    }
    return 0;
}

int String_2D_To_1D(char **grid , char *string , int g_y , int g_x ){
    if(grid == NULL){
        return 1;
    }
    if(string == NULL){
        return 1;
    }
    int i = 0;
    for(i = 0 ; i < g_x ; i++){
        string[i] = grid[g_y][i];
    }
    return 0;
}

int Number_Scanner(char **grid ,const int x , const int y , int step_y , int is_scaned[][8] , char *number_buffer){
    String_Wipe(number_buffer , 8);
    int pos_y = 1
       ,i = 0 
       ,j = 0
       ,k = 0
       ,comparison_value = 0
       ,same_coords = 0
       ,scanned_buffer[7] = {0}
       ,coordinate_buffer[7] = {0}
       ,org_buffer[7] = {0};
    short scanable = 0
         ,fwscan = 0
         ,bwscan = 0
         ,sorted = 0;
    pos_y -= step_y * -1; 
    for(i = 0 ; i < 7 ; i++){
        if(is_scaned[pos_y][i] == x){
            scanable = 1;
        }
    }
    if(scanable == 1){
        return 1;
    }
    i = 0;
    while(fwscan == 0){
        isasciinum(grid[y][x + i]){
            scanned_buffer[i] = x + i;
            i++;
            continue;
        }
        fwscan = 1;
    }
    j = 0;
    // this is gonna result in the same x value twice :skull:
    while(bwscan == 0){
        if(x - j < 0){
            bwscan = 1;
        }
        isasciinum(grid[y][x - j]){
            scanned_buffer[i] = x - j;
            j++;
            i++;
            continue;
        }
        bwscan = 1;
    }
    // just delete the value lol :clueless:
    for(j = 0 ; j < i ; j++){
        comparison_value = scanned_buffer[j];
        for(k = 0 ; k < i ; k++){
            if(comparison_value == scanned_buffer[k] && j != k){
                scanned_buffer[j] = 255;
                j++;
                continue;
            }
        } 
    }
    for(j = 0 ; j < i ; j++){
        if(scanned_buffer[j] == 255){
            same_coords++;
            continue;
        }
        coordinate_buffer[j-same_coords] = scanned_buffer[j];
        is_scaned[pos_y][j-same_coords] = scanned_buffer[j];
    }
    // printf("pos_y %i\n" , pos_y);
    // time to set x from small to big bc coordinate system be like
    // HAHA SORTING ALGO TIME FUCK ME i need so many fucking buffers
    j = 0;
    while(j < i-same_coords){
        comparison_value = 0;
        for(k = 0 ; k < i-same_coords ; k++){
            if(k == j){
                continue;
            }
            if(coordinate_buffer[j] > coordinate_buffer[k]){
                comparison_value++;
            }
        }
        org_buffer[comparison_value] = coordinate_buffer[j];
        j++;
    }
    for(j = 0 ; j < i-same_coords ; j++){
        number_buffer[j] = grid[y][org_buffer[j]];
        // printf("%c ," , number_buffer[j]);
    }
    // printf("\n");
    return 0;
}

int Find_Those_Numbers(char **grid  , coords s_pos , int g_height , int g_length , int *ret){
    if(grid == NULL){
        return 0;
    }
    const int x_step[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1}
             ,y_step[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1 };
    //i love maths quadrants
    int i = 0
       ,x = s_pos.x
       ,y = s_pos.y
       ,is_scanned[3][8] = {0};
    char number_buffer[8] = {0};
    printf("symbol: %c\n" , s_pos.symbol);
    for(i = 0 ; i < 8 ; i++){
        if(x + x_step[i] < 0 || x + x_step[i] >= g_length){
           continue; 
        }
        if(y + y_step[i] < 0 || y + y_step[i] >= g_height){
            continue;
        }
        isasciinum(grid[y + y_step[i]][x + x_step[i]]){
            snif(Number_Scanner(grid , x + x_step[i] , y + y_step[i], y_step[i] , is_scanned , number_buffer) , 0 , continue)
            printf("%i\n" , atoi(number_buffer));
            *ret += atoi(number_buffer);
        }
    } 
    return 0;
}

int Data_Analysis(char **grid , int g_height , int g_length , coords *symbol_pos , int *ret){
    int y_pos = 0
       ,i = 0
       ,symbol_total = 0;
    char buffer[1024] = {0};

    for(y_pos = 0 ; y_pos < g_height ; y_pos++){
        if(String_Wipe(buffer , g_length) != 0) return 1;
        if(String_2D_To_1D(grid , buffer , y_pos , g_length)!= 0) return 1;
        Symbol_Finder(buffer , g_length , y_pos , symbol_pos , &symbol_total);
    }
    for(i = 0 ; i < symbol_total ; i++){
        snif(Find_Those_Numbers(grid , symbol_pos[i] , g_height , g_length , ret) , 0 , return 1)
    }


    return 0;
}

int main(){
    char filename[] = "input.txt";
    int grid_height = 0
       ,grid_legth = 0
       ,total_numbers = 0;
    coords *symbol_pos = malloc(sizeof(coords) * 4096);
    snif(CSV_Size(filename , &grid_height , &grid_legth) , 0 , printf("skill issue 1"))
    char **grid = malloc(sizeof(char *)*grid_height);
    for(int i = 0 ; i < grid_legth ; i++){
        grid[i] = (char*)malloc(sizeof(char)*grid_legth);
    }
    snif(CSV_Input(filename , grid , grid_height , grid_legth) , 0 , printf("skill issue 2"))
    snif(Data_Analysis(grid , grid_height , grid_legth , symbol_pos , &total_numbers) , 0 , printf("skill issue 3"))
    printf("totalnumb = %i",total_numbers);
    for(int i = 0 ; i < grid_height ; i++){
        free(grid[i]);
    }
    free(grid);
}