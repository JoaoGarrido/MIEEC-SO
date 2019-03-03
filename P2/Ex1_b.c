#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main(int argc, char **argv){
    if(argc != 3) return 0;
    int fd = open(argv[1], O_RDONLY);
    assert(fd != -1);
    int fd_new = open(argv[2], O_RDONLY); 
    assert(fd_new == -1); //abort if file already exists
    fd_new = open(argv[2], O_RDWR|O_CREAT, S_IRWXU);//NOTE: O_RDWR permission and user read/write user permissions
    char buf[64];
    int Read_return = 1, Error_return = 1;
    while(Read_return != 0){
        Read_return = read(fd,buf,BUFFER_SIZE);
        assert(Read_return != -1);
        Error_return = write(fd_new,buf,Read_return);
    }
}