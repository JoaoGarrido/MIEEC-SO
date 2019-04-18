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

typedef struct _result{
    int result;
}result_struct;

void *sum(void *arg){
    int *values = (int *) arg;
    result_struct *r = malloc(sizeof(result_struct));
    r->result = values[0]+values[1];
    return (void *) r;
}

void *sub(void *arg){
    int *values = (int *) arg;
    result_struct *r = malloc(sizeof(result_struct));
    r->result = values[0]-values[1];
    return (void *) r;
}

void *mult(void *arg){
    input_struct *values = (input_struct *)arg;
    result_struct *r = malloc(sizeof(result_struct));
    r->result = values->a*values->b;
    return (void *) r;    
}

void *divi(void *arg){
    input_struct *values = (input_struct *)arg;
    result_struct *r = malloc(sizeof(result_struct));
    r->result = values->a/values->b;
    return (void *) r;
}

int main(int argc, char *argv[]){
    //Reading input
    if(argc != 3) return -1;
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    //Array argument
    int args[2];
    args[0]=a;
    args[1]=b;
    //Struct argument
    input_struct input;
    input.a = a;
    input.b = b;
    pthread_t id[4];
    result_struct *r_main[4];
    pthread_create(&(id[0]), NULL, sum, (void *) args);
    pthread_create(&(id[1]), NULL, sub, (void *) args);
    pthread_create(&(id[2]), NULL, mult, (void *) &input);
    pthread_create(&(id[3]), NULL, divi, (void *) &input);
    for(int i = 0; i < 4; i++){
        pthread_join((id[i]), (void **) &(r_main[i]));
    }
    printf("Sum: %d\n", r_main[0]->result );
    printf("Sub: %d\n", r_main[1]->result );
    printf("Mult: %d\n", r_main[2]->result );
    printf("Div: %d\n", r_main[3]->result );
    for(int i = 0; i < 4; i++){
        free(r_main[i]);
    }
}