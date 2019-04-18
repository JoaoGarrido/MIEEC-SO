#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int a = 0;
int b = 0;

void *sum(void *arg){
    int res=a+b;
    printf("Sum: %d\n", res);
}

void *sub(void *arg){
    int res=a-b;
    printf("Sub: %d\n", res);
}

void *mult(void *arg){
    int res=a*b;
    printf("Mult: %d\n", res);
}

void *divi(void *arg){
    int res=a/b;
    printf("Div: %d\n", res);
}

int main(int argc, char *argv[]){
    if(argc != 3) return -1;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    pthread_t id[4];
    /*
    pthread_attr_t attr[4];
    for(int i = 0; i < 4; i++){
        pthread_attr_init(&(attr[i]));
    }*/
    pthread_create(&(id[0]), NULL, sum, NULL);
    pthread_create(&(id[1]), NULL, sub, NULL);
    pthread_create(&(id[2]), NULL, mult, NULL);
    pthread_create(&(id[3]), NULL, divi, NULL);
    for(int i = 0; i < 4; i++){
        pthread_join((id[i]), NULL);
    }
}