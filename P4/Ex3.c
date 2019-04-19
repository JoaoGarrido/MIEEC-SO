#define DEBUG 0

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if (DEBUG == 1)
#include <errno.h>
#endif

void *pid_tid(void *args){
    int *localArg = (int *) args;
    printf("TID: %ld\n",  pthread_self());
    return (void *) localArg;
}

int main(int argc, char const *argv[]){
    assert(argc > 1);
    int n = strtol(argv[1], NULL, 10);
    
    pthread_t *ThreadID = malloc( n * sizeof(pthread_t *) );
    int *args = malloc( n * sizeof(int *) );
    
    for(int i = 0; i < n; i++){
        args[i] = i+1;
        pthread_create( &(ThreadID[i]), NULL, pid_tid, (void *) &(args[i]) );
        #if (DEBUG == 1)
        int a=pthread_create( &(ThreadID[i]), NULL, pid_tid, (void *) &(args[i]) );
        if(a == EAGAIN){
            printf("Can't create more threads\n");
            exit(0);
        }
        #endif
    }
    
    for(int i = 0; i < n; i++){
        int *ThreadReturn;
        pthread_join(ThreadID[i], (void **) &(ThreadReturn) );
        printf("Return Value of thread %ld: %d\n", ThreadID[i], *(ThreadReturn) );
    }
    
    free(ThreadID);
    free(args);
    
    return 0;
}
