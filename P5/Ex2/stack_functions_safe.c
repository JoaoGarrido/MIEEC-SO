#include "stack_functions_safe.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void push(el_stack **HEAD, int integer, char *text){
    el_stack *newElement = (el_stack *) malloc(sizeof(el_stack));
    if(newElement == NULL){
        printf("Error allocating memory!\n");
        exit(1);
    }
    pthread_mutex_lock(&lock);
    newElement->next = *HEAD;
    *HEAD = newElement;
    pthread_mutex_unlock(&lock);
    newElement->n = integer;
    newElement->str = text;
}

void pop(el_stack **HEAD){
    pthread_mutex_lock(&lock);
    if(*HEAD == NULL){
        printf("Stack empty or error!\n");
        return;
    }
    el_stack *tmp = *HEAD;
    *HEAD = tmp->next;
    pthread_mutex_unlock(&lock);
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

long count(el_stack **HEAD){
    long counter = 0;
    el_stack *tmp; 
    tmp = *HEAD;
    printf("Number of stack elements:\n");
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    return counter;
}