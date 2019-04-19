#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void *arrayInitializer(void *args){
    printf("OLA CARAGO %ld\n", pthread_self());
}

int main(int argc, char const *argv[]){
    assert(argc > 2);
    int arraySize = strtol(argv[1], NULL, 10);
    int nThreads = strtol(argv[2], NULL, 10);

    pthread_t *ThreadID = malloc(sizeof(pthread_t *) * nThreads);
    
    for(int i = 0; i < nThreads; i++){
        pthread_create(&(ThreadID[i]), NULL, arrayInitializer, NULL);
    }
    
    for(int i = 0; i < nThreads; i++){
        pthread_join(ThreadID[i], NULL);
    }
    
    printf("%d %d\n", arraySize, nThreads); 
    return 0;
}
