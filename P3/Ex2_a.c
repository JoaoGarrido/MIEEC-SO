#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[], char *envp[]){
    assert(argc > 1);
    const char* text1 = "\nENVP:\n";
    int fd = open(argv[1],O_RDWR|O_CREAT, S_IRWXU);
    write(fd,text1,strlen(text1));
    for(int i = 0; envp[i] != NULL; i++){
        write(fd,envp[i],strlen(envp[i]));  
        write(fd,"\n",1);
    }    
    return 0;
}