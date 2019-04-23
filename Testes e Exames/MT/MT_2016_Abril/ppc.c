//#include "match_line.c"
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct _threadWork{
    pthread_t threadID;
    const char *searchString;
    const char *fileName;
    int fileDescriptor;
    int *stringLine;
    int nOccurrences;
}threadWork;

void* search(void *args){
    threadWork *Args = (threadWork *) args;
    Args->fileDescriptor = open(Args->fileName, O_RDONLY, S_IRUSR);
    assert(Args->fileDescriptor != -1);
    int aux = 0, cap = 1;

    Args->stringLine = malloc( sizeof(int));
    while( (aux = match_line(Args->fileDescriptor, (char *) Args->searchString)) != 0 ){
        if(Args->nOccurrences == cap){
            cap = cap*2;
            Args->stringLine = realloc(Args->stringLine, sizeof(int)* cap);
        }
        Args->stringLine[Args->nOccurrences++] = aux;
    }
    close(Args->fileDescriptor);
    return 0;
}

void print_Thread_Work(threadWork *Args){
    for(int i = 0; i<Args->nOccurrences; i++)
        printf("%s:\t%d\n", Args->fileName, Args->stringLine[i]);
}

int main(int argc, char const *argv[]){
    assert(argc > 2);
    int nFiles = argc-2;
    threadWork *ThreadWork = malloc( sizeof(threadWork) * nFiles );
    for(int i = 0; i < nFiles; i++){
        ThreadWork[i].searchString = argv[1];
        ThreadWork[i].fileName = argv[i+2];
        ThreadWork[i].nOccurrences = 0;
        pthread_create(&ThreadWork[i].threadID, NULL, search, (void *) &ThreadWork[i]);
    } 
    for(int i = 0; i < nFiles; i++)
        pthread_join(ThreadWork[i].threadID, NULL);
    for(int i = 0; i < nFiles; i++)
        print_Thread_Work(&ThreadWork[i]);
    free(ThreadWork);
    return 0;
}
