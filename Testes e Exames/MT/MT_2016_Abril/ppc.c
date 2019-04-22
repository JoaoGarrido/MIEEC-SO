#include "match_line.c"
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_NUMBER_STRING 500

typedef struct _threadWork{
    pthread_t threadID;
    const char *searchString;
    const char *fileName;
    int fileDescriptor;
    int stringLine[MAX_NUMBER_STRING];
    int nOccurrences;
}threadWork;

void* search(void *args){
    threadWork *Args = (threadWork *) args;
    Args->fileDescriptor = open(Args->fileName, O_RDONLY, S_IRUSR);
    assert(Args->fileDescriptor != -1);
    int i = 0;
    for(i = 0; (i == 0 || Args->stringLine[i-1] != 0) && i < MAX_NUMBER_STRING; i++){
        Args->stringLine[i] = match_line(Args->fileDescriptor, (char *) Args->searchString);
    }
    Args->nOccurrences = i-1;
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
        pthread_create(&ThreadWork[i].threadID, NULL, search, (void *) &ThreadWork[i]);
    } 
    for(int i = 0; i < nFiles; i++)
        pthread_join(ThreadWork[i].threadID, NULL);
    for(int i = 0; i < nFiles; i++)
        print_Thread_Work(&ThreadWork[i]);
    return 0;
}
