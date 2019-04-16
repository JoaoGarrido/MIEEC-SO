#include "stack_functions.h"

void push(stack_structure STACK, int integer, char *text){
    stack_el *newElement = malloc(sizeof(stack_el));

    newElement->n = integer;
    newElement->str = text;
    
    
}

void pop(stack_structure STACK){

}

void show(){

}