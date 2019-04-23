//#include "du.c"
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_NAME 1024
#define MAX_THREADS 500
long long du(int fd);

typedef struct{
    pthread_t tID;
    char fileName[MAX_FILE_NAME];
    int fileDescriptor;
    long long int fileLength;
}threadArgs;


void *thrfunc(void *args){
    threadArgs *ThreadArgs = (threadArgs *)args;
    if( (ThreadArgs->fileDescriptor = open( ThreadArgs->fileName, O_RDONLY, S_IRUSR)) < 0){
        return NULL;
    };
    ThreadArgs->fileLength = du(ThreadArgs->fileDescriptor);
    close(ThreadArgs->fileDescriptor);
    return NULL;
}

int main(int argc, char const *argv[]){
    int length, cap = 1, size = 0;
    //threadArgs *ThreadArgs = malloc( sizeof(threadArgs) * cap);
    threadArgs ThreadArgs[MAX_THREADS];
    while( (length = read(STDIN_FILENO, ThreadArgs[size].fileName, MAX_FILE_NAME)) > 0){
        /*if(size == cap){
            cap = cap*2;
            ThreadArgs = realloc(ThreadArgs ,sizeof(threadArgs) * cap);
        }*/
        if(length <= 0)
            break;
        ThreadArgs[size].fileName[length-1] = 0;
        size++;
    }
    for(int i = 0; i < size; i++){
        pthread_create( &ThreadArgs[i].tID, NULL, thrfunc , (void *)&ThreadArgs[i]);
    }
    for(int i = 0; i < size;i++){
        pthread_join(ThreadArgs[i].tID, NULL);
    }
    for(int i = 0; i < size; i++){
        printf("%s:\t%lld bytes\n", ThreadArgs[i].fileName, ThreadArgs[i].fileLength );
    }
    //free(ThreadArgs);
    return 0;
}

