#include <stdio.h>
#include <string.h>


int my_strlen(char *str){
    int i = 0;
    while(str[i] != '\\') ++i;
    return i;
}

int main(int argc, char **argv){
    //Note: "!\n" is not valid in bash for whatever reason... find out
    printf("strlen %ld\n", strlen(argv[1]));
    printf("my_strlen %d\n", my_strlen(argv[1]));
}