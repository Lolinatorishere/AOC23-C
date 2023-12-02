#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    char string[256];
    int str_size;
};

typedef struct data data;

int CSV_Size(char *file_dir , int *ret){
    FILE  *CSV_IN;
    char buffer[1024];
    int i = 0;
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 1024 , CSV_IN)){
        i++;
        }
    *ret = i;
    }
}

int CSV_Input(char *file_dir , data *to_memory){
    FILE  *CSV_IN;
    int i = 0
       ,j = 0 
       ,values = 0;
    char buffer[1024];
    CSV_IN = fopen(file_dir , "r");
    if(CSV_IN == NULL){
        return 1;
    }else{
        while(fgets(buffer , 1024 , CSV_IN)){
            j = 0;
            values = sscanf(buffer , "%s\n"
            ,to_memory[i].string);
            while (buffer[j] != '\0'){
                j++;
            }
            to_memory[i].str_size = j;
            if(values == 1){
                i++;
            }else{
                return 1;
            }
        }
    }
    fclose(CSV_IN);
}

int Data_Analysis(data *in_memory , int filesize , int *answertotal){
    int number = 0
        ,num_bool = 0;
    char stringnumber[2] = "\0";
    for(int i = 0 ; i <= filesize ; i++){
        num_bool = 0;
        *stringnumber = '\0';
        for(int j = 0 ; j < in_memory[i].str_size ; j++){
            if(in_memory[i].string[j] >= 48 && in_memory[i].string[j] <= 57){
                if(num_bool == 0 ){
                    stringnumber[0] = in_memory[i].string[j];
                }
                stringnumber[1] = in_memory[i].string[j];
                num_bool++;
            }
        }
        printf("%s\n",stringnumber);
        number = atoi(stringnumber);
        *answertotal += number;
    }
    return 0;
}

int main(){
    char filename[] = "input.txt";
    int filesize = 0
       ,answertotal;
    CSV_Size(filename , &filesize);
    data *analysis = malloc(sizeof(data)*filesize);
    CSV_Input(filename , analysis);
    Data_Analysis(analysis , filesize , &answertotal);
    printf("%i",answertotal);    
    free(analysis);
}
    