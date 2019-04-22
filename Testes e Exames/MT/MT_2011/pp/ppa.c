/* ppa.c
a) Escreva um programa que processe os argumentos da linha
de comando, inicialize a estrutura de tipo "vector_t" a usar e,
finalmente, mostre o estado do vector partilhado por via da invocação
da função "print_vector()" (incluída em util.c)

Exemplo de invocação:
     ./ppa 6000 4000
*/

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

vector_t vector;	// estrutura de dados a partilhar pelos threads

int main(int argc, char *argv[]) {
     setbuf(stdout, NULL);

     // a preencher com o seu código!
     assert(argc > 2);
	vector.len = (atoi(argv[1]) + atoi(argv[2]))*1000;
     vector.cnt[0] = 0;
     vector.cnt[1] = 0;
     vector.next = 0;
     vector.array = malloc( sizeof(int) * vector.len );

     print_vector(&vector);
     return 0;
}
