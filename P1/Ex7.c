#include <stdio.h>
#include <stdlib.h>

#define DEBUG

int main(int argc, char **argv){
    if(argc != 2){
        printf("How to use example: ./a.out 10\n ");
        return -1;
    }
    char *p1 = 0;
    int v1 = 0, v2 = 0;
    int endianInteger = atoi(argv[1]);
    printf("%d\n", endianInteger);
    for(int i = 0; i < (int)sizeof(endianInteger); i++){
        p1 = (char *) &endianInteger+i;
        v1 = v1 | (*p1 << ((i)*8) ); 
        v2 = (v2 | *p1) << 8;
        
        #ifdef DEBUG
        //printf("p1: %d\n", p1);
        printf("*(p1+%d) %#x\n",i,*p1);
        printf("v1(HEX): %#x\n", v1);
        //printf("v2(HEX): %#x\n", v2);
        #endif
    }
    printf("little endian integer: %d (HEX: %#x)\n", v1, v1);
    printf("big endian integer: %d (HEX: %#x)\n", v2, v2);
    if(v1 == endianInteger)
        printf("Littel endian\n");
    else if(v2 == endianInteger)
        printf("Big endian\n");
    else
        printf("ERROR!\n");
}