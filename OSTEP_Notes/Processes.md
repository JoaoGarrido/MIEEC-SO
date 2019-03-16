---
tags:
  - OSTEP
---

#Processes and Processes API

#4.1 The process abstraction

A process is the name that we call to the abstraction created by the OS to a program
The process has a part of the memory that can address(address space), special registers like a program counter(PC) and stack pointer(manages the address space related to stack), I/O information, etc 

#4.2 Process API
Create()
Destroy()
Wait() //for I/O
Status()
MiscellaneousControl() //Example: Suspend and resume process

#4.3 Process Creation

The program content from the disk is loaded into memory
The stack is allocated
The heap is (de)allocated when needed by malloc() and free()
File descriptors for I/O are initialized
The OS starts to the entry point of the program, main() and transfers the control to the CPU

#4.4 Process states

3 different states:
Running
Ready -> waiting for the decision to run by the scheduler
Blocked -> waiting for I/O

Example:
Ready->Running->Blocked(by I/O)->(I/O done)Ready->Running....

#4.5 Data structures in the scheduler

The OS keeps track of information about the processes(Process list) so it can decide which process should run, save the information when the scheduler decides to run other process, know the state of a given process,etc
When the process ends other process or the OS will check if it executed sucessfully and if so it will clear the information about the extinct process

