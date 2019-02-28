#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main(int argc, char **argv){
    int fd = open(argv[1], O_RDONLY);
    assert(fd != -1);
    char buf[64];
    int Read_return = 1, Error_return = 1;
    while(Read_return != 0){
        Read_return = read(fd,buf,BUFFER_SIZE);
        assert(Read_return != -1);
        Error_return = write(STDOUT_FILENO,buf,Read_return);
    }
}