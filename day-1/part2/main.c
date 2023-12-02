#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tldw in_memory[i].string[j]
#define stringwrite(kmax)\
for(int k = 0 ; k < kmax ; k++){\
    bufferstring[k] = in_memory[i].string[j+k];\
}\
bufferstring[kmax] = '\0';\
return 0;

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

int String_To_Number(char *input , char *ret){
    if(strcmp(input , "one\0") == 0){
        *ret = '1';
        return 0;
    }
    if(strcmp(input , "nine\0") == 0){
        *ret = '9';
        return 0;
    }
    if(strcmp(input , "eight\0") == 0){
        *ret = '8';
        return 0;
    }
    if(strcmp(input , "four\0") == 0){
        *ret = '4';
        return 0;
    }
    if(strcmp(input , "five\0") == 0){
        *ret = '5';
        return 0;
    }
    if(strcmp(input , "six\0") == 0){
        *ret = '6';
        return 0;
    }
    if(strcmp(input , "seven\0") == 0){
        *ret = '7';
        return 0;
    }
    if(strcmp(input , "two\0") == 0){
        *ret = '2';
        return 0;
    }
    if(strcmp(input , "three\0") == 0){
        *ret = '3';
        return 0;
    }
    return 1;
}

int Char_Checker(data *in_memory , char bufferstring[] , int i , int j){
    if(tldw == 'o'){
        if(j+2 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+2] == 'e'){
            stringwrite(3)
        }
    }
    if(tldw == 'n'){
        if(j+3 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+3] == 'e'){
            stringwrite(4)
        }
    }
    if(tldw == 'e'){
        if(j+4 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+4] == 't'){
            stringwrite(5)
        }
    }
    if (tldw == 'f'){
        if(j+3 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+3] == 'r'){
            stringwrite(4)
        }
        if(in_memory[i].string[j+3] == 'e'){
            stringwrite(4)
        }
    }
    if(tldw == 's'){
        if(j+2 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+2] == 'x'){
            stringwrite(3)
        }
        if(j+4 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+4] == 'n'){
            stringwrite(5)
        }
    }
    if(tldw == 't'){
        if(j+2 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+2] == 'o'){
            stringwrite(3)
        }
        if(j+4 >= in_memory[i].str_size){
            return 1;
        }
        if(in_memory[i].string[j+4] == 'e'){
            stringwrite(5)
        }
    }
    return 1;
}

int Data_Analysis(data *in_memory , int filesize , int *answertotal){
    int number = 0
        ,num_bool = 0;
    char stringnumber[2] = {0}
        ,ret_string = '\0'
        ,bufferstring[128] = {0};
    for(int i = 0 ; i <= filesize ; i++){
        num_bool = 0;
        *stringnumber = '\0';
        for(int j = 0 ; j < in_memory[i].str_size ; j++){
            if(Char_Checker(in_memory , bufferstring , i , j) == 1){
                strcpy(bufferstring , "\0");
            }
            if(String_To_Number(bufferstring , &ret_string) == 0){
                if(num_bool == 0){
                    stringnumber[0] = ret_string;
                    num_bool++;
                }
                stringnumber[1] = ret_string;
            }
            if(in_memory[i].string[j] >= 48 && in_memory[i].string[j] <= 57){
                if(num_bool == 0){
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
    