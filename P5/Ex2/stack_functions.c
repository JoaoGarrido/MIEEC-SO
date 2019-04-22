#include "stack_functions.h"
#include <stdlib.h>
#include <stdio.h>

void push(el_stack **HEAD, int integer, char *text){
    el_stack *newElement = (el_stack *) malloc(sizeof(el_stack));
    if(newElement == NULL){
        printf("Error allocating memory!\n");
        exit(1);
    }
    newElement->next = *HEAD;
    newElement->n = integer;
    newElement->str = text;
    *HEAD = newElement;
}

void pop(el_stack **HEAD){
    if(*HEAD == NULL){
        printf("Stack empty or error!\n");
        return;
    }
    el_stack *tmp = *HEAD;
    *HEAD = tmp->next;
    free(tmp);
}

void show(el_stack **HEAD){
    el_stack *tmp; 
    tmp = *HEAD;
    printf("STACK:\n");
    while(tmp != NULL){
        printf("%d | %s\n", tmp->n, tmp->str);
        tmp = tmp->next;
    }
    printf("---------------\n");
}