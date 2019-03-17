#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <stdio.h>


void printEnvVar(const char *fileName, char *envp[]){
    const char *text = "ENVP:\n";
    int fd = open(fileName, O_RDWR | O_CREAT, S_IRWXU);
    write(fd, text, strlen(text));
    for (int i = 0; envp[i] != NULL; i++)
    {
        write(fd, envp[i], strlen(envp[i]));
        write(fd, "\n", 1);
    }
}

int main(int argc, char const *argv[], char *envp[])
{
    assert(argc > 1);
    int pid = fork();
    wait(NULL);
    if (pid < 0)
    {
        printf("Fork failed ;_;\n");
    }
    else if (pid == 0)
    {
        printEnvVar(argv[2],envp);
        printf("HELLO I AM THE CHILD! xD(PID: %d)\n", getpid());
    }
    else
    {
        printEnvVar(argv[1],envp);
        printf("Just a filthy parent(PID: %d) of an useful child(PID: %d)\n", getpid(), pid);
    }
    return 0;
}