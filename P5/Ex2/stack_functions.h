/*
Starts:
    Pointer to null
    push(elememt)

*/

#define STACK_FUNCTIONS_H "stack_functions.h"
typedef struct _stack_structure{
    stack_el *FirstElement;
    stack_el *LastElement;
} stack_structure;

typedef struct _stack_el{
		char *str;              /* String to be printed in show() */
		int n;                  /* Integer to be printed in show() */
		stack_el *next;  /* Link to next stack element */
}stack_el;

void push(stack_structure STACK, int integer, char *text);

void pop(stack_structure STACK);

void show(stack_structure STACK);