#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
    int gameid;
    int gamesets;   
    int blue[8];
    int red[8];
    int green[8];
};

typedef struct data data;

int CSV_Size(char *file_dir , int *ret){
    FILE  *CSV_IN;
    char buffer[2048];
    int i = 0;
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 2048 , CSV_IN)){
        i++;
        }
    *ret = i;
    }
    return 0;
}

int Cube_Type(char *string , int *ret){
    if(string[0] == 'r'){
        *ret = 1;
        return 0;
    }
    if(string[0] == 'g'){
        *ret = 2;
        return 0;
    }
    if(string[0] == 'b'){
        *ret = 3;
        return 0;
    }
    return 1;
}

int CSV_Input(char *file_dir , data *to_memory , int filesize){
    FILE  *CSV_IN;
    int i = 0
       ,j = 0
       ,l = 0
       ,k = 0
       ,cubecolour = 0
       ,game_set = 0
       ,gamebool = 0
       ,numberbool = 0
       ,stringbool = 0;
    char buffer[2048] = {0}
        ,cube_buffer[6] = {0}
        ,cube_count[3] = {0};
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(i < filesize){
            fgets(buffer , 2048 , CSV_IN);
            j = 0;
            gamebool = 0;
            stringbool = 0;
            to_memory[i].gameid = i+1;
            game_set = 0;
            strcpy(cube_buffer , "\0");
            while(stringbool == 0){
                if(buffer[j] == '\n' || buffer[j] == '\0'){
                    stringbool++;
                }
                while(buffer[j] != ':' && gamebool == 0){
                    j++;
                }
                gamebool++;
                if(buffer[j] >= 48 && buffer[j] <= 57){
                    cube_count[l] = buffer[j];
                    l++;
                    k = 0;
                }else if(buffer[j] >= 97 && buffer[j] <= 122){
                    cube_buffer[k] = buffer[j];
                    k++;
                    l = 0;
                }
                if(buffer[j] == ',' || buffer[j+1] == '\n' || buffer[j] == ';'){
                    if (Cube_Type(cube_buffer , &cubecolour) != 0){
                        return 1;
                    }
                    switch(cubecolour){
                    case 1:
                        to_memory[i].red[game_set] = atoi(cube_count);
                    break;

                    case 2:
                        to_memory[i].green[game_set] = atoi(cube_count);
                    break;

                    case 3:
                        to_memory[i].blue[game_set] = atoi(cube_count);
                    break;

                    default:
                        return 1;
                    break;
                    }
                    numberbool++;
                }
                if(buffer[j] == ';' || buffer[j+1] == '\n' || buffer[j+1] == '\0'){
                    game_set++;
                }
                if(numberbool != 0){
                    for(int foo = 0 ; foo < 4 ; foo++){
                        cube_count[foo] = '\0';
                    } 
                    numberbool = 0;
                }
                j++; 
            }
            to_memory[i].gamesets = game_set;
            i++;
        }
    }
    fclose(CSV_IN);
    return 0;
}

int Data_Wipe(data *in_memory , int filesize){
    for(int i = 0 ; i < filesize ; i++){
        for(int j = 0 ; j <= 8 ; j++){
            in_memory[i].red[j] = 0;
            in_memory[i].blue[j] = 0;
            in_memory[i].green[j] = 0;
        }
        in_memory[i].gameid = 0;
    }
}

int Data_Analysis(data *in_memory , int filesize){
    int game_qualified = 0
       ,total_ids = 0;
    for(int i = 0 ; i <= filesize ; i++){
        game_qualified = 0;
        for(int j = 0 ; j <= in_memory[i].gamesets && game_qualified == 0; j++){
            if(in_memory[i].red[j] > 12){
                game_qualified = 1;
            }
            if(in_memory[i].green[j] > 13){
                game_qualified = 1;
            } 
            if(in_memory[i].blue[j] > 14){
                game_qualified = 1;
            } 
        }
        if(game_qualified == 0){
            total_ids += in_memory[i].gameid; 
        }
    }
    printf("total ids qualified == %i\n" , total_ids);
    return 0;
}

int main(){
    char filename[] = "input.txt";
    int filesize = 0;
    CSV_Size(filename , &filesize);
    printf("filesize %i", filesize);
    data *analysis = malloc(sizeof(data)*filesize);
    Data_Wipe(analysis , filesize);
    if(CSV_Input(filename , analysis , filesize) == 1){
        printf("skill issue");
        return 1;
    }
    if(Data_Analysis(analysis , filesize) != 0){
        printf("skill issue");
        return 1;
    }
    // for(int i = 0 ; i < filesize ; i++){
    //     printf("game %i\n" , analysis[i].gameid);
    //     for(int j = 0 ; j < analysis[i].gamesets ; j++){
    //         printf("\tgameset:%i\n\t\tred: %i\n\t\tgreen %i\n\t\tblue: %i\n"
    //                ,j 
    //                ,analysis[i].red[j] 
    //                ,analysis[i].green[j]
    //                ,analysis[i].blue[j]);
    //     }
    // }
}