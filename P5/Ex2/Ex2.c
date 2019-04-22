#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define SAFE 1
#ifdef SAFE  
#include "stack_functions_safe.h"
#else
#include "stack_functions.h"
#endif

#define N_NEW_ENTRIES 10

typedef struct _threadArgs{
    pthread_t ThreadID;
    el_stack **HEAD;
    int number;
    char *string;
    int nNewEntries;
}threadArgs;

void* thread_Push(void *Args){
    threadArgs *largs = (threadArgs*)Args;
    for(int i = 0; i < largs->nNewEntries; i++){
        push(largs->HEAD,largs->number,largs->string);
    }
}

void* thread_Pop(void *Args){
    threadArgs *largs = (threadArgs*)Args;
    for(int i = 0; i < largs->nNewEntries; i++){
        pop(largs->HEAD);
    }
}

void* thread_Show(void *Args){
    threadArgs *largs = (threadArgs*)Args;
    show(largs->HEAD);
}

int main(int argc, char const *argv[]){

    el_stack *HEAD = NULL;
    for(int i = 0; i < 10; i++){
        push(&HEAD,i,"XD");
    }
    show(&HEAD);
    for(int i=0; i<10; i++){
        pop(&HEAD);
        show(&HEAD);
    }
    //pop(&HEAD);
    
    //Multi-Threading Tests
    //Push Threads
    long nThreads = strtol(argv[1], NULL, 10);
    threadArgs *tArgs = malloc( sizeof(threadArgs) * nThreads );
    for(int i = 0; i < nThreads; i++){
        tArgs[i].HEAD = &HEAD;
        tArgs[i].number = i;
        tArgs[i].string = "Do or do not, threre is no try";
        tArgs[i].nNewEntries = N_NEW_ENTRIES;
        pthread_create(&(tArgs[i].ThreadID), NULL, thread_Push, (void *) &tArgs[i] );
    }
    for(int i = 0; i < nThreads; i++){
        pthread_join(tArgs[i].ThreadID, NULL);
    }
    show(&HEAD);
    printf("HEAD = %d\n", HEAD->n);
    long counter = count(&HEAD);
    printf("%ld\n", counter );
    
    //Pop Threads
    for(int i = 0; i < nThreads; i++){
        pthread_create(&(tArgs[i].ThreadID), NULL, thread_Pop, (void *) &tArgs[i] );
    }
    for(int i = 0; i < nThreads; i++){
        pthread_join(tArgs[i].ThreadID, NULL);
    }
    show(&HEAD);
    printf("%ld\n", count(&HEAD) );
    
    free(tArgs);
    return 0;
}
