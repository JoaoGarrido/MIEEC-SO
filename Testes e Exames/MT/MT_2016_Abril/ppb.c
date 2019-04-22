#include "match_line.c"
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct _threadWork{
    pthread_t threadID;
    const char *searchString;
    const char *fileName;
    int fileDescriptor;
}threadWork;

void* search(void *args){
    threadWork *Args = (threadWork *) args;
    Args->fileDescriptor = open(Args->fileName, O_RDONLY, S_IRUSR);
    assert(Args->fileDescriptor != -1);
    int aux = 1;
    while( aux ){
        aux = match_line(Args->fileDescriptor, (char *) Args->searchString);
        if(aux){
            printf("%s:\t%d\n", Args->fileName, aux);
        }
    }
    return 0;
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
    return 0;
}
