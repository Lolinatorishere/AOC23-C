#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define snif(STRING1 , STRING2 , RESULT) \
    if(STRING1 != STRING2){\
        RESULT;\
    }

#define isasciinum(STRING)\
    if(STRING >= 48 && STRING <= 57)

int String_Wipe(char *string , int s_length){
    if(string == NULL){
        return 1;
    }
    for(int i = 0 ; i < s_length ; i++){
        string[i] = '\0';
    }
    return 0;
}

int CSV_Size(char *file_dir , int *card_amt , int *number_max , int *win_index){
    FILE  *CSV_IN;
    int i = 0
       ,j = 0 
       ,total_nums = 0;
    char buffer[1024];
    short scanning = 1;
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 1024 , CSV_IN)){
            i++;
        }
        while(buffer[j] != ':'){
            j++;
        }
        j++;
        while(buffer[j] != '\n'){
            if(buffer[j] == '\0'){
                break;
            }
            if(buffer[j] == '|'){
                *win_index = total_nums;
            }
            isasciinum(buffer[j]){
                scanning = 0;
            }
            while(scanning == 0){
                isasciinum(buffer[j]){
                    j++;
                    continue;
                }
                total_nums++;
                scanning = 1;
            }
            j++;
        }
    }
    *card_amt = i;
    *number_max = total_nums;
    fclose(CSV_IN);
}

int CSV_Input(char *file_dir , int **to_memory){
    FILE  *CSV_IN;
    int i = 0
       ,j = 0 
       ,k = 0
       ,total_nums = 0;
    char buffer[1024]
        ,number_buffer[4];
    short scanning = 1;
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 1024 , CSV_IN)){
            while(buffer[j] != ':'){
                j++;
            }
            j++;
            while(buffer[j] != '\n'){
                if(buffer[j] == '\0'){
                    break;
                }
                isasciinum(buffer[j]){
                    String_Wipe(number_buffer , 4);
                    scanning = 0;
                }
                while(scanning == 0){
                    isasciinum(buffer[j]){
                        number_buffer[k] = buffer[j];
                        k++;
                        j++;
                        continue;
                    }
                    to_memory[i][total_nums] = atoi(number_buffer);
                    k = 0;
                    scanning = 1;
                    total_nums++;
                }
                j++;
            }
            total_nums = 0;
            i++;
            j = 0;
        }
    }
    fclose(CSV_IN);
}

int Data_Analysis(int **in_memory , int card_total , int num_p_card , int winners , double *ret){
    int i = 0
       ,j = 0
       ,k = 0
       ,points_p_line = 0;
    double points_total = 0;
    short jscan = 0
         ,kscan = 0;
    while(i < card_total){
        while(jscan == 0){
            if(j >= winners){
                jscan = 1;
                continue;
            }
            k = winners;
            while(kscan == 0){
                if(k >= num_p_card){
                    kscan = 1;
                }
                if(in_memory[i][k] == in_memory[i][j]){
                    kscan = 1;
                    points_p_line++; 
                }
                k++;
            }
            kscan = 0;
            j++;
        }
        if(points_p_line != 0){
            points_total += pow(2 , points_p_line - 1);
        }
        j = 0;
        jscan = 0;
        points_p_line = 0;
        i++;
    }
    *ret = points_total;
    return 0;
}

int main(){
    char filedir[] = "input.txt";
    int card_total = 0
       ,winners = 0
       ,numbers_per_card = 0;
    double answer = 0;
    snif(CSV_Size(filedir , &card_total , &numbers_per_card , &winners) , 0 , return 1)
    // CSV_Input(filedir , &games);
    int **cards = malloc(sizeof(int *)*card_total);  
    for(int i = 0 ; i < card_total ; i++){
        cards[i] = malloc(sizeof(int) * numbers_per_card+1);
    }
    snif(CSV_Input(filedir , cards) , 0 , return 1)
    snif(Data_Analysis(cards , card_total , numbers_per_card , winners , &answer) , 0 , return 1);
    printf("answer : %.0f\n" , answer);
    for(int i = 0 ; i < card_total ; i++){
        free(cards[i]);
    }
    free(cards);
}