#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>       
#include <unistd.h>

#define DEBUG 0

#define MAX_THREADS 3

void *pid_tid(void *args){
    int *localArg = (int *) args;
    printf("PID: %d | TID: %ld\n", getpid(),  pthread_self());
    
    #if (DEBUG == 1)
    if( !(*localArg)) printf("localArg: %ld\n", localArg);
    #endif
    
    return (void *) localArg;
}

int main(int argc, char const *argv[]){
    pthread_t ThreadID[MAX_THREADS];
    int args[3];
    
    #if (DEBUG==1)
    int *ThreadReturn[MAX_THREADS];
    #endif

    for(int i = 0; i < MAX_THREADS; i++){
        args[i] = i+1;
        pthread_create( &(ThreadID[i]), NULL, pid_tid, (void *) &(args[i]) );
    }
    
    for(int i = 0; i < MAX_THREADS; i++){
        #if (DEBUG==0)
        int *ThreadReturn[MAX_THREADS];
        #endif
        pthread_join(ThreadID[i], (void **) &(ThreadReturn[i]) );
        printf("Return Value of thread %ld: %d\n", ThreadID[i], *(ThreadReturn[i]) );
    }

    #if (DEBUG==1)
    printf("args: %ld | ThreadReturn: %ld", args, ThreadReturn[0] );
    #endif

    return 0;
}
