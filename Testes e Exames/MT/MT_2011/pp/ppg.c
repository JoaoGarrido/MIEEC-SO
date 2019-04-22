/* ppg.c

g) Desenvolva um novo programa que garanta que, em qualquer
instante da inicialização do vector partilhado, a diferença máxima (em
milhares) entre o nº de elementos inicializado por cada thread não
excede um dado valor. Isto permitirá um maior grau de "entremeação" -
e competição - na execução dos threads. Tal diferença máxima de
elementos inicializados será apresentada como um parâmetro adicional
na linha de comando. Por ex., com uma invocação na forma :

   ./ppg 5000 5000 1

o seu programa deverá criar 2 threads, o primeiro dos quais deverá
inicializar 5000 milhares de elementos com o valor 0 e o segundo com
5000 milhares com o valor 1, sendo que em qualquer instante o nº de
elementos inicializado por cada thread não pode diferir em mais de
1000.

O seu programa deverá usar semáforos ou variáveis de condição para
sincronizar correctamente os 2 threads de inicialização sem "busy
waiting."

Nota: Assuma que o programa é invocado sempre com argumentos
cujos valores são tais que o valor absoluto da diferença dos 2
primeiros argumentos não excede o valor do 3º argumento.

*/
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define N_THREADS 2
vector_t vector;	// estrutura de dados a partilhar pelos threads


// a preencher com o seu código!
typedef struct{
     int ID;
     int nElements;
     pthread_t tID;
     pthread_cond_t *cond;
     int maxDifference;
}threadArgs;

void *arrayInit(void *args){
    threadArgs *ThreadArg = (threadArgs *)args;
    printf ("Thread %ld running\n", pthread_self());
    printf ("Thread %d: cnt = %d, vp = %p\n", ThreadArg->ID, ThreadArg->nElements, &vector);
    while(vector.cnt[ThreadArg->ID] < ThreadArg->nElements){
        pthread_mutex_lock(&vector.lock);
        while( vector.cnt[ThreadArg->ID]-vector.cnt[(ThreadArg->ID+1) % N_THREADS] >= (ThreadArg->maxDifference) ){
            pthread_cond_wait(ThreadArg->cond, &vector.lock);
        } 
        vector.array[vector.next++] = ThreadArg->ID;
        vector.cnt[ThreadArg->ID]++;
        if( vector.cnt[(ThreadArg->ID+1) % N_THREADS]-vector.cnt[ThreadArg->ID] < (ThreadArg->maxDifference) ){
            pthread_cond_signal(ThreadArg->cond);
        }        
        pthread_mutex_unlock(&vector.lock);
    }
    print_vector(&vector);
    return NULL;    
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    // a preencher com o seu código!
    assert(argc > 3);
    vector.len = (atoi(argv[1]) + atoi(argv[2]))*1000;
    vector.cnt[0] = 0;
    vector.cnt[1] = 0;
    vector.next = 0;
    vector.array = malloc( sizeof(int) * vector.len );
    pthread_mutex_init(&vector.lock, NULL);
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_t checkerID;
    chkr_arg_t checkerArgs;
    checkerArgs.argc = argc;
    checkerArgs.argv = argv;
    checkerArgs.vector = &vector;
    pthread_create(&checkerID, NULL, checker, (void *)&checkerArgs);
    threadArgs ThreadArgs[N_THREADS]; 
    for(int i = 0; i < N_THREADS; i++){
        ThreadArgs[i].ID = i;
        ThreadArgs[i].nElements = atoi(argv[i+1])*1000;
        ThreadArgs[i].maxDifference = atoi(argv[3])*1000;
        ThreadArgs[i].cond = &cond;
        pthread_create(&ThreadArgs[i].tID, NULL, arrayInit, (void *)&ThreadArgs[i]);
    }
    for(int i = 0; i < N_THREADS; i++)
        pthread_join(ThreadArgs[i].tID, NULL);
    printf ("Main thread exiting\n");

    pthread_join(checkerID, NULL);

    pthread_mutex_destroy(&vector.lock);
    
    print_vector(&vector);
    free(vector.array);
    return 0;
}
// a preencher com o seu código!
