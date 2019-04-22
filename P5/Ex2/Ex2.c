#include "stack_functions.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
    el_stack *HEAD = NULL;
    for(int i = 0; i < 10; i++){
        push(&HEAD,i,"XD");
    }
    show(&HEAD);
    for(int i=0; i<10; i++){
        pop(&HEAD);
        show(&HEAD);
    }
    pop(&HEAD);
    return 0;
}
