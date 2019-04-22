/* ppd.c

d) Desenvolva um novo programa que, para além de fazer o
que é pedido nas alíneas anteriores, faça com que os 2 threads de
inicialização inicializem *mesmo* o vector partilhado, mas sem
tentarem evitar erros de competição ("race conditions").  A impressão
da informação já pedida na alínea anterior irá permitir ver o trabalho
que foi efectuado.  

*Nota:* aqui já deve ser possível observar que há erros de
competição, mesmo para um vector partilhado com um nº de elementos
relativamente pequeno! É óbvio, pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppd 6000 4000
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
	while(vector.cnt[ThreadArg->ID] != ThreadArg->nElements ){
          vector.array[vector.next++] = ThreadArg->ID;
          vector.cnt[ThreadArg->ID]++;
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
     threadArgs ThreadArgs[N_THREADS]; 
	for(int i = 0; i < N_THREADS; i++){
          ThreadArgs[i].ID = i;
          ThreadArgs[i].nElements = atoi(argv[i+1])*1000;
		pthread_create(&ThreadArgs[i].tID, NULL, arrayInit, (void *)&ThreadArgs[i]);
     }
	for(int i = 0; i < N_THREADS; i++)
		pthread_join(ThreadArgs[i].tID, NULL);
	printf ("Main thread exiting\n");

     print_vector(&vector);
     return 0;
}

// a preencher com o seu código!
