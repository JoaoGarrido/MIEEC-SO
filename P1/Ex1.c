#include <stdio.h>

#define FIB_0 0
#define FIB_1 1
#define N_Elements 10

void fibIterative(int *v,int total){
    for(int i = 2; i < total; i++){
        v[i] = v[i-2] + v[i-1];
    }
}

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

int main(){
    int fib_Array[N_Elements] = {0};
    fib_Array[0] = FIB_0;
    fib_Array[1] = FIB_1;
    fibIterative(fib_Array, N_Elements);
    print_fib_Array(fib_Array, N_Elements, "ITERATIVE");
    fibRecursive(fib_Array+2, N_Elements, FIB_0, FIB_1);
    print_fib_Array(fib_Array, N_Elements,"RECURSIVE");
}