#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <stdio.h>


int main(int argc, char const *argv[], char *envp[])
{
    /*
    NOTES:
    OG Process->fork->wait for child->fork->wait for grand child->print grand child->return 3->print child->return 2->print parent->return 0
    */
    //Entry points 
    pid_t pid_gc = 1;
    pid_t pid = fork();
    int wstatus;
    wait(&wstatus); //parent waits for child
    if(pid == 0){
        pid_gc = fork();
        wait(&wstatus); //child waits for grand child
    }
    //Common Code
    if (pid < 0 || pid_gc < 0)
    {
        printf("Fork failed ;_;\n");
    }
    else
    {
        printf("PID: %d || ParentPID: %d", getpid(), getppid());
        if(pid_gc == 0){ //grand child
            printf("\n");
            return 3;
        } 
        else if(pid == 0){ //child
            printf(" || Status of child:% d\n",WEXITSTATUS(wstatus));
            return 2;
        }
        else{ //parent
            printf(" || Status of child: %d\n",WEXITSTATUS(wstatus));
        }
    }
    return 0;
}
