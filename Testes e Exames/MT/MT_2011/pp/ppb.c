/* ppb.c

b) Desenvolva um novo programa que, para além de fazer o
que é pedido em a) crie os 2 threads de inicialização. Cada
um destes threads deverá invocar a função printf() do seguinte
modo:

	printf ("Thread %d running\n", pthread_self());

O thread principal deverá esperar que cada um dos threads de inicialização
termine, após o que deverá imprimir:

	printf ("Main thread exiting\n");

Nota: Nesta alínea não precisa de passar qualquer argumento aos threads
de inicialização.

Exemplo de invocação:
     ./ppb 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define N_THREADS 2
vector_t vector;	// estrutura de dados a partilhar pelos threads

// a preencher com o seu código!
void *arrayInit(void *args){
	printf ("Thread %ld running\n", pthread_self());
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
	for(int i = 0; i < N_THREADS; i++)
		pthread_create(&tID[i], NULL, arrayInit, NULL);
	for(int i = 0; i < N_THREADS; i++)
		pthread_join(tID[i], NULL);
	printf ("Main thread exiting\n");

	print_vector(&vector);
	return 0;
}

// a preencher com o seu código!
