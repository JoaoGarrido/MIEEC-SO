#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct _input_struct
{
    int a, b;
}input_struct;

int resSum, resSub, resMult, resDiv;

void *sum(void *arg){
    int *values = (int *) arg;
    resSum = values[0]+values[1];
    //resSum = *(int*)arg+*(int *)(arg+sizeof(int));
}

void *sub(void *arg){
    int *values = (int *) arg;
    resSub = values[0]-values[1];
    //resSub = *(int*)arg-*(int *)(arg+sizeof(int));
}

void *mult(void *arg){
    input_struct *values = (input_struct *)arg;
    resMult = values->a*values->b;
}

void *divi(void *arg){
    input_struct *values = (input_struct *)arg;
    resDiv = values->a/values->b;
}

int main(int argc, char *argv[]){
    //Reading input
    if(argc != 3) return -1;
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    //Array
    int args[2];
    args[0]=a;
    args[1]=b;
    //Struct
    input_struct input;
    input.a = a;
    input.b = b;
    pthread_t id[4];
    /*
    pthread_attr_t attr[4];
    for(int i = 0; i < 4; i++){
        pthread_attr_init(&(attr[i]));
    }*/
    pthread_create(&(id[0]), NULL, sum, (void *) args);
    pthread_create(&(id[1]), NULL, sub, (void *) args);
    pthread_create(&(id[2]), NULL, mult, (void *) &input);
    pthread_create(&(id[3]), NULL, divi, (void *) &input);
    for(int i = 0; i < 4; i++){
        pthread_join((id[i]), NULL);
    }
    printf("Sum: %d\n", resSum);
    printf("Sub: %d\n", resSub);
    printf("Mult: %d\n", resMult);
    printf("Div: %d\n", resDiv);
}