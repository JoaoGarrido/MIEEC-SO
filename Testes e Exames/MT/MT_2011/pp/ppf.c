/* ppf.c

f) Desenvolva um novo programa, corrijindo a versão da
alínea e) por forma a que, garantidamente, não haja "race conditions",
mesmo para um vector partilhado com um elevado nº de elementos!

Exemplo de invocação:
     ./ppf 6000 4000
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
}threadArgs;

void *arrayInit(void *args){
     threadArgs *ThreadArg = (threadArgs *)args;
     printf ("Thread %ld running\n", pthread_self());
     printf ("Thread %d: cnt = %d, vp = %p\n", ThreadArg->ID, ThreadArg->nElements, &vector);
     while(vector.cnt[ThreadArg->ID] != ThreadArg->nElements){
          pthread_mutex_lock(&vector.lock);
          vector.array[vector.next++] = ThreadArg->ID;
          vector.cnt[ThreadArg->ID]++;
          pthread_mutex_unlock(&vector.lock);
     }
     print_vector(&vector);
     return NULL;
}

int main(int argc, char *argv[]) {
     setbuf(stdout, NULL);

     // a preencher com o seu código!
     assert(argc > 2);
     vector.len = (atoi(argv[1]) + atoi(argv[2]))*1000;
     vector.cnt[0] = 0;
     vector.cnt[1] = 0;
     vector.next = 0;
     vector.array = malloc( sizeof(int) * vector.len );
     pthread_mutex_init(&vector.lock, NULL);
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
          pthread_create(&ThreadArgs[i].tID, NULL, arrayInit, (void *)&ThreadArgs[i]);
     }
     for(int i = 0; i < N_THREADS; i++)
          pthread_join(ThreadArgs[i].tID, NULL);
     printf ("Main thread exiting\n");

     pthread_join(checkerID, NULL);
     pthread_mutex_destroy(&vector.lock);
     print_vector(&vector);
     return 0;
}
// a preencher com o seu código!
