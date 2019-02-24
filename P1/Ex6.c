#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG 1

char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int no_months(char *mon1, char *mon2){
    int m1 = -1, m2 = -1;
    int size_string_1 = strlen(mon1), size_string_2 = strlen(mon2);
    for(int i = 0; i < 12; i++){
        if(strncasecmp(mon1, *(months+i), size_string_1) == 0)
            m1 = i;
        else if(strncasecmp(mon2, *(months+i), size_string_2) == 0) 
            m2 = i;
        #ifdef DEBUG
        printf("%d:\n", i);
        printf("m1 = %d\n", m1);
        printf("m2 = %d\n", m2);
        #endif

        if(m1 != -1 && m2 != -1) break;
    }

    if(m1 == -1 || m2 == -1)
        return -1;
    else if(m2 > m1)
        return (m2-m1);
    else
    {
        #ifdef DEBUG
        printf("m1 = %d\n", m1);
        printf("m2 = %d\n", m2);
        #endif
        return (12-m1+m2);
    }
}

void print_months(char **text){
    for(int i = 0; i < 12; i++) printf("%s\n", *(text+i));
}

int main(int argc, char **argv){
    print_months(months);
    int n_months = -1;
    if(argc == 3){
        n_months = no_months(argv[1], argv[2]);
    }

    if(n_months != -1)  
        printf("Number of months between %s and %s : %d\n", argv[1], argv[2], n_months);
    else
        printf("Insert valid month(Example: jan, feb, mar,...)\n");
}