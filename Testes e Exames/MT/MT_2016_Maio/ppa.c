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

#define MAX_SIZE_STRING 1024
long long du(int fd);

typedef struct{
    pthread_t tID;
    char filename[MAX_SIZE_STRING];
    int fileDescriptor;
}threadArgs;


void *thrfunc(void *args){
    threadArgs *ThreadArgs = (threadArgs *)args;
    printf("%s:\t%lld bytes\n", ThreadArgs->filename, du(ThreadArgs->fileDescriptor) );
    return NULL;
}

int main(int argc, char const *argv[]){
    threadArgs *ThreadArgs = malloc( sizeof(threadArgs) * 1);
    int length = read(STDIN_FILENO, ThreadArgs[0].filename, MAX_SIZE_STRING );
    ThreadArgs[0].filename[length-1] = 0;
    ThreadArgs[0].fileDescriptor = open( ThreadArgs[0].filename, O_RDONLY, S_IRUSR);
    
    pthread_create( &ThreadArgs[0].tID, NULL, thrfunc , (void *)&ThreadArgs[0]);
    pthread_join(ThreadArgs[0].tID, NULL);
    free(ThreadArgs);
    return 0;
}

