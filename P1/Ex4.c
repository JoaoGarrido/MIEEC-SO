#include <stdio.h>
#include <stdlib.h>

//Preprocessing
/* AllocType
dynamic allocation -> 1
static allocations -> 0
*/
#define AllocType 1

/*
strtoll -> 1
atoi -> 0
*/
#define StringToIntType 1

#define FIB_0 0
#define FIB_1 1

void fibRecursive(int *v,int total, int n1, int n2){
    if(total > 2) {
        *v = n1+n2;
        fibRecursive(++v, --total, n2, *v);
    }
}

void print_fib_Array(int *v,int total, char Text[30]){
    printf("%s\n", Text);
    printf("First %d fibonacci elements:\n", total);
    for(int i = 0; i < total;i++) printf("%d\n", v[i]);
    printf("END;\n");
}

int main(int argc, char **argv){
    #if StringToIntType == 0
    int n = atoi(argv[1]);
    #else
    char *p;
    int n = strtol(argv[1], &p, 10);
    #endif
    if(n>47){
        n=47;
        printf("Nmax = 47\n");  
    } 

    #if AllocType == 0
    int fib_Array[48] = {0};
    #else
    int *fib_Array = 0;
    fib_Array = malloc(n*sizeof(int));
    #endif
    
    fib_Array[0] = FIB_0;
    fib_Array[1] = FIB_1;
    fibRecursive(fib_Array+2, n, FIB_0, FIB_1);
    print_fib_Array(fib_Array, n,"RECURSIVE");
}