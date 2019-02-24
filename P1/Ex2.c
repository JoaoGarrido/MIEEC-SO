#include <stdio.h>

int main(){
    //a)
    printf("char: %ldB\n", sizeof(char));
    printf("short: %ldB\n", sizeof(short));
    printf("int: %ldB\n", sizeof(int));
    printf("long: %ldB\n", sizeof(long));
    printf("long long: %ldB\n", sizeof(long long));
    //b)
    int a[10];
    struct complex {
        double re, im;
    } z;
    char *hello = "Hello, World!";
    printf("a: %ldB\n", sizeof(a));
    printf("z: %ldB\n", sizeof(z));
    printf("hello: %ldB\n", sizeof(hello));
    //c)
    printf("a[0]: %ldB\n", sizeof(a[0]));
    printf("*hello: %ldB\n", sizeof(*hello));
}