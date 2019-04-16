#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 64


int main(int argc, char *argv[]){
    int fd_r = open(argv[1], O_RDONLY);
    int fd_w;
    if(argc >= 3){
        fd_w = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    }
    else
        dup2(fd_w,STDOUT_FILENO);
    int Read_return = 1, Error_return = 1;
    char buf[64];
    while(Read_return != 0){
        Read_return = read(fd_r,buf,BUFFER_SIZE);
        assert(Read_return != -1);
        Error_return = write(fd_w,buf,Read_return);
    }
}