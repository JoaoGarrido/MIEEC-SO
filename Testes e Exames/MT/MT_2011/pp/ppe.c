/* ppe.c
e) Desenvolva um novo programa que, além de fazer o que é
pedido nas alíneas anteriores, cria um thread de verificação, i.e. que
executa a função checker() declarada em util.h. O argumento
desta função deve ser um apontador para uma variável do tipo
chkr_arg_t definida também em util.h, e aqui reproduzida:

typedef struct {
    int argc;          // to be initialized with argc of main()
    char **argv;       // to be initializedwith argv of main()
    vector_t *pvector; // to be initialized with pointer to the shared structure
} chkr_arg_t;

O thread de verificação deve ser criado antes dos threads de
inicialização e esperado pelo thread principal apenas depois daqueles
terem terminado.  

*Nota:* aqui também ainda devem ser patentes
os erros de competição, mesmo para um vector partilhado com um nº de
elementos relativamente pequeno, pois ainda pois não houve esforço de
sincronização no acesso ao vector!

Exemplo de invocação:
     ./ppe 6000 4000
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
    print_vector(&vector);
    return 0;
}

// a preencher com o seu código!
