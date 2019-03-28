/*
Explanation:
without locks(mutex) the threads will have a race condition:
sometimes they will not sync the counter value increment by the other threads and will overwrite that value
because of this we need to use mutex to sync the threads  
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define with_Mutexes 1
#define I_MAX 3

volatile uint64_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *incr(void *args){
    uint64_t *nInc = (uint64_t *)args;
    for(int i = 0; i < *nInc;i++){
#ifdef with_Mutexes
        pthread_mutex_lock(&lock);
#endif
        ++counter;
#ifdef with_Mutexes
        pthread_mutex_unlock(&lock);
#endif
    } 
}

int main(int argc, char *argv[]){
    assert(argc >= 2);
    uint64_t nIncrements_per_thread = 0;
    sscanf(argv[1], "%ld", &nIncrements_per_thread);
    pthread_t id[3];
#ifdef with_Mutexes
    pthread_mutex_init(&lock,NULL);
#endif   
    for(int i=0; i < I_MAX; i++)    pthread_create(&(id[i]), NULL, incr, (void *)&nIncrements_per_thread);
    for(int i=0; i < I_MAX; i++)    pthread_join(id[i],NULL);
#ifdef with_Mutexes
    pthread_mutex_destroy(&lock);
#endif       
    printf("Counter value: %ld\n", counter);
}