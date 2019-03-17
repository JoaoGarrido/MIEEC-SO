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
    pid_t pid = fork();
    int status = -1;
    wait(&status);
    if(pid < 0){
        printf("Fork failed ;_;\n");
    }
    else if(pid == 0){
        /* execve:
        argv[0] should contain the filename that's going to be executed
        last element of argv array should be NULL
        */
        argv[0]="gcc";
        argv[argc]=NULL;
        execve("/usr/bin/gcc",(char **)argv,envp);
    }
    else{
        printf("Compilation exit code: %d\n", WEXITSTATUS(status));
    }
    return 0;
}