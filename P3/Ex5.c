#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <stdio.h>

int main(int argc, char const *argv[], char *envp[]){
    assert(argc > 2);
    argv[0]="gcc";
    argv[argc]=NULL;
    execve("/usr/bin/gcc",(char **)argv,envp);
}
        
    