/*
NOTES:
(1)
CORRECT WAY
int cs;
wait(&cs);
WRONG WAY
int *cs;
wait(cs);

(2)
wait(...) for every child to terminate
waitpid(...) specific child

(3)
execv(char *path, char *argv[], char *envp[])
execv(gcc)->execv(argv[0],argv[1],)
argv[0]->"/usr/bin/gcc"
argv[1]->"-Wall"
*/
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[], char *envp[]){
    const char* text1 = "\nargv:\n", *text2 = "\nENVP:\n";
    write(STDOUT_FILENO,text1,strlen(text1));
    for(int i = 0; i < argc;i++){
        write(STDOUT_FILENO,argv[i],strlen(argv[i]));
        write(STDOUT_FILENO,"\n",1);
    }    
    write(STDOUT_FILENO,text2,strlen(text2));
    for(int i = 0; envp[i] != NULL; i++){
        write(STDOUT_FILENO,envp[i],strlen(envp[i]));  
        write(STDOUT_FILENO,"\n",1);
    }    
    return 0;
}