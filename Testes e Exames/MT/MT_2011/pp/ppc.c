/* ppc.c

c) Desenvolva um novo programa, que além de fazer o que é pedido
nas alíneas anteriores, deverá fazer com que cada um dos threads
de inicialização invoque a função printf() do seguinte modo:

	printf ("Thread %d: cnt = %d, vp = %p\n", X, Y, Z);

onde X representa o identificador do thread (ou 0 ou 1), Y representa
o nº de elementos que o thread deverá inicializar, e Z o endereço da
estrutura de dados do tipo vector_t partilhada pelos threads de
inicialização.  Antes de terminar cada thread deverá ainda
invocar a função print_vector() já referida.

Nota: Cada thread deverá invocar esta instrução com um valor X diferente.

Exemplo de invocação:
     ./ppc 6000 4000
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
}threadArgs;

void *arrayInit(void *args){
     threadArgs *ThreadArg = (threadArgs *)args;
	printf ("Thread %ld running\n", pthread_self());
     printf ("Thread %d: cnt = %d, vp = %p\n", ThreadArg->ID, ThreadArg->nElements, &vector);
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
	pthread_t tID[2];
     threadArgs ThreadArgs[2]; 
	for(int i = 0; i < N_THREADS; i++){
          ThreadArgs[i].ID = i;
          ThreadArgs[i].nElements = atoi(argv[i+1])*1000;
		pthread_create(&tID[i], NULL, arrayInit, (void *)&ThreadArgs[i]);
     }
	for(int i = 0; i < N_THREADS; i++)
		pthread_join(tID[i], NULL);
	printf ("Main thread exiting\n");

     print_vector(&vector);
     return 0;
}

// a preencher com o seu código!
