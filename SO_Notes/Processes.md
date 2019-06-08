---
tags:
  - OSTEP
  - Processes
  - Chapter 4
  - Chapter 5
---

# Processes and Processes API

## 4.1 The process abstraction

A process is the name that we call to the abstraction created by the OS to run a program

The process has a part of the memory that can address(address space), special registers like a program counter(PC) and stack pointer(manages the address space related to stack), I/O information, etc 

I/O are slower than the processor and memory so the OS chooses which process should run to optimize the system performance.

There are 2 types of multiprocessing:
* Real paralllism -> In multiprocessor or multicore systems processes may run simultaneously
* Pseudo parallelism -> In uniprocessor or when there are more active processes than cores, the OS assigns which process the processor should run

## 4.2 Process API

* Create()
* Destroy()
* Wait() //for I/O
* Status()
* MiscellaneousControl() //Example: Suspend and resume process

## 4.3 Process Creation

1. The program content from the disk is loaded into memory
2. The stack is allocated and initialized
3. The heap is (de)allocated when needed by malloc() and free()
4. File descriptors for I/O are initialized(stdin, stdout, stderr)
5. The OS starts to the entry point of the program, main() and transfers the control to the CPU

## 4.4 Process states

3 different states:
* Running
* Ready -> waiting for the decision to run by the scheduler (CPU executing another process)
* Waiting -> waiting for I/O or certain event

Example:
Ready->Running->Blocked(by I/O)->(I/O done)Ready->Running....

## 4.5 Data structures in the scheduler

The OS keeps track of information about the processes(Process list) so it can decide which process should run, save the information when the scheduler decides to run other process, know the state of a given process,etc.

When the process ends other process or the OS will check if it executed sucessfully and if so it will clear the information about the extinct process

## 5.1 The fork() system call

Acts as an entry point into the program that is running at the time creating a process that is an almost exact copy of the process that called him with its own memory address, process ID and registers. 

Even though the process is a copy the entry point it's not main() but fork()!

To distinguish the parent and child processes we can use the return value of fork()-> PID if parent,0 if child

If we don't use wait() the scheduler can choose which process will run first!

*NOTE:*
Use getpid() and getppid() to get the PID of the process or parent process running at the time!

## 5.2 The wait() system call

```c
pid_t wait(int *wstatus);
```
Description:

waits for any child process to end

Params:
* int *wstatus 
> If no information is needed about how wait returned we can use NULL and it will simply execute wait(NULL) (read man wait for more info)

Returns:

returns PID on sucess, -1 on error

```c
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
 Description:

waits for some child process to end

Params:
* pid_t pid -> Process ID generally but...
> < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
>
> -1     meaning wait for any child process.
>
> 0      meaning wait for any child process whose process group ID is equal to that of the calling process. 
* int *wstatus same as wait()
* int options some special options (man wait)

Returns:

returns child PID on sucess, -1 on error

## 5.3 The exec() system call

Runs a program that, unlike fork(), is different from the  the program that calls it.

The exec() overwrites the program that is running (stack, heap and other parts of the space of the program are re-initialized). This means that the process that called exec() is not terminated, it's replaced with a new program.

There are 6 variants of exec(): execl, execlp(), execle(),execv(), execvp(), and execvpe(). 

```c
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
```
 Description:

Replaces current process image with a new process image 

Params:
* const char *path
> Path to the file that is going to be executed
>
> in execvp() case it's the file but this file needs to be in PATH
* ichar *const argv[]
> address of the char array that contains the args
>
> *NOTE:*
>
>         argv[0] should contain the filename that's going to be executed
>         last element of argv array should be NULL

Returns:

returns only on error(-1)

fork() and execv() simplifies the process creation.  

## _exit()

Exits the process

*NOTE:*

Different from exit()