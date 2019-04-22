#define STACK_FUNCTIONS_H "stack_functions.h"

typedef struct _el_stack{
		char *str;              /* String to be printed in show() */
		int n;                  /* Integer to be printed in show() */
		struct _el_stack *next;  /* Link to next stack element */
}el_stack;

void push(el_stack **HEAD, int integer, char *text);

void pop(el_stack **HEAD);

void show(el_stack **HEAD);