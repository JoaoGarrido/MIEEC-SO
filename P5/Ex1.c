#include <pthread.h>
#include <assert.h>


#define with_Mutexes 1

//Needs to be declared before include sfun.c or lock inside sfun.c will not be declared
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


#if with_Mutexes
#define SumFunc sfun
#include "sfun.c"
#else
#define SumFunc tfun
#include "tfun.c"
#endif


#define I_MAX 3



int main(int argc, char const *argv[]){


    assert(argc >= 2);
    int nIncrements_per_thread = 0;
    sscanf(argv[1], "%d", &nIncrements_per_thread);
    
    long int counter = 0;
    pthread_t id[3];
    targ_t main_targ[3];
    
    pthread_mutex_init(&lock,NULL);
    
    for(int i=0; i < I_MAX; i++){
        main_targ[i].id = i;
        main_targ[i].cnt = &counter;
        main_targ[i].n = nIncrements_per_thread;
        pthread_create(&(id[i]), NULL, SumFunc, (targ_t *)&main_targ[i]);
    }   
    for(int i=0; i < I_MAX; i++)    pthread_join(id[i],NULL);
    
    pthread_mutex_destroy(&lock);
    
    printf("Counter value: %ld\n", counter);

    return 0;
}
