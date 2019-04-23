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
long long du(int fd);

typedef struct{
    pthread_t tID;
    char fileName[MAX_FILE_NAME];
    int fileDescriptor;
}threadArgs;


void *thrfunc(void *args){
    threadArgs *ThreadArgs = (threadArgs *)args;
    if( (ThreadArgs->fileDescriptor = open( ThreadArgs->fileName, O_RDONLY, S_IRUSR)) < 0){
        return NULL;
    };
    printf("%s:\t%lld bytes\n", ThreadArgs->fileName, du(ThreadArgs->fileDescriptor) );
    close(ThreadArgs->fileDescriptor);
    return NULL;
}

int main(int argc, char const *argv[]){
    threadArgs *ThreadArgs = malloc( sizeof(threadArgs) * 1);
    int length = read(STDIN_FILENO, ThreadArgs[0].fileName, MAX_FILE_NAME );
    ThreadArgs[0].fileName[length-1] = 0;    
    pthread_create( &ThreadArgs[0].tID, NULL, thrfunc , (void *)&ThreadArgs[0]);
    pthread_join(ThreadArgs[0].tID, NULL);
    free(ThreadArgs);
    return 0;
}

