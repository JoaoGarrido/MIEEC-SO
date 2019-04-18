/*
This way there will be warnings because we are casting an integer to void * when returning from thread functions
*/

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct _input_struct{
    int a, b;
}input_struct;

void *sum(void *arg){
    int *values = (int *) arg;
    //return (void *) ( *(int*)arg+*(int *)(arg+sizeof(int)) );
    return (void *) (values[0]+values[1]);
}

void *sub(void *arg){
    int *values = (int *) arg;
    //return (void *) ( *(int*)arg-*(int *)(arg+sizeof(int)) );
    return (void *) (values[0]-values[1]);
}

void *mult(void *arg){
    input_struct *values = (input_struct *)arg;
    return (void *) (values->a*values->b);
}

void *divi(void *arg){
    input_struct *values = (input_struct *)arg;
    return (void *) (values->a/values->b);
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
    int res[4];

    pthread_create(&(id[0]), NULL, sum, (void *) args);
    pthread_create(&(id[1]), NULL, sub, (void *) args);
    pthread_create(&(id[2]), NULL, mult, (void *) &input);
    pthread_create(&(id[3]), NULL, divi, (void *) &input);
    for(int i = 0; i < 4; i++){
        pthread_join((id[i]), (void **) &(res[i]));
    }
    
    printf("Sum: %d\n", (int) res[0] );
    printf("Sub: %d\n", (int) res[1] );
    printf("Mult: %d\n", (int) res[2] );
    printf("Div: %d\n", (int) res[3] );
}