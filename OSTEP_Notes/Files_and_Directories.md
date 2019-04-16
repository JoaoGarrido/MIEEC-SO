---
tags:
  - OSTEP
  - File System
---

# Files and Directories

## 39.3 Creating Files
To create files we call the open() system call:

```c
int fd = open("foo", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
```

It returns a file descriptor (similar to a pointer to an object of type file)

Flags:

* 0_CREAT -> Creates the file

* 0_WRONLY -> Write permission only

* 0_TRUNC -> If the file exists, removes the content in it

* S_IRUSR -> User can read

* S_IWUSR -> User can write
## 39.4 Reading and Writing Files

The read() and write() system calls use the fd to operate and after each operation, the fd offsets the number of bytes read/written  

### Reading: read() system call
```c
ssize_t read(int fd, void *buf, size_t count);
```

Description:
> Reads from file (referenced by the fd) count bytes into the buffer (buf). 

Params:
> int fd (file descriptor) 
> 
> void *buf -> buffer where the data will go
>
> size_t count -> Max number of bytes that will be read 

Returns:
> Returns the number of bytes that were read
>> Zero indicates end of file
>>
>> -1 indicates error


### Writing: write() system call
```c
* ssize_t write(int fd, const void *buf, size_t count);
```

Description:
> Writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.

Params:
> int fd (file descriptor) 
> 
> void *buf -> buffer where the data will come
>
> size_t count -> Max number of bytes that will be written 

Returns:
> Returns the number of bytes that were written
>> Zero indicates end of space
>>
>> -1 indicates error

Returns the number of bytes that were written.
## 39.5 Reading and Writing, But Not Sequentially
```c
off_t lseek(int fd, off_t offset, int whence);
```

Jumps offset bytes from certain position. The initial position is determined by whence:

* If whence is SEEK_SET, the offset is set to offset bytes.

* If whence is SEEK_CUR, the offset is set to its currentlocation plus offset bytes.

* If whence is SEEK_END, the offset is set to the size ofthe file plus offset bytes.

After executing lseek(), if we read() or write() from the file descriptor it will start at the position after lseek(). The OS keeps the information about the offset.
## 39.6 Shared File Table Entries: fork() and dup()

fork() -> Parent and childs use the same Open File Table

int newfd = dup(int oldfd) -> Creates a copy of the file descriptor with the lowest unused number

dup2(int oldfd, newfd) -> Same as dup() but can choose the number of newfd

Example:

Redirecting output
```c
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
```