#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
    int fd_new = open(argv[2], O_RDWR|O_CREAT|O_APPEND, S_IRWXU);
    char *str = "aa";
    strcat(argv[2],str);
    int fd_to_merge =  open(str, O_RDONLY);
    while(fd_to_merge != -1){
        str[strlen(str)-1] = ;
    }
    return 0;
}