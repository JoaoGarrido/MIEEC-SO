---
tags:
  - OSTEP
  - Threads
  - Concurrency
  - Chapter 26
  - Chapter 27
---

# Threads and Threads API

Threads create separate points of execution in a program, just like processes, but they share the same address space and can acess the same data easily.

Each thread has an independent stack (Stack Pointer, Program counter and static variables) and share the same heap in the same address space.

## 26.1 Why use threads?
To get parallelization into our system we use threads.

Threads are also used to perform slow I/O without blocking the main thread.

## 26.2 An Example: Thread Creation
Even tho a thread is created first, the order that the threads are executed is handled by the scheduler.

## 26.3-5 Why It Gets Worse: Shared Data / The Heart of the Problem: Uncontrolled Scheduling / The Wish For Atomicity
When we share data across threads, the scheduler can create race conditions () resulting in non deterministic behaviour and unexpected results.

The piece of code that when executed across multiple threads can create race conditions, we call critical section.

We want that critical section run in mutual exclusion, this guarantees that if one thread is executing the critical the other are prevented from running.

When we want to run a piece of code "as a unit" we call that executing atomically (all of it runs or none of it runs). To do this we use synchronization primitives.

## 27.1 Thread Creation
```c
int pthread_create(pthread_t *thread, 
    const pthread_attr_t *attr, 
    void *(*start_routine) (void *), 
    void *arg);
```
Description:
> Creates a thread that runs the fuction start_routine with arguments arg.
> 

Params:
> pthread_t *thread
>> Identifier to the thread. For example: pthread_t t1; pthread_create(&t1,....); 
> 
> const pthread_attr_t *attr
>> NULL makes the attributes default
>
> void *(*start_routine) (void *) 
>> Executes start_routine() -> function: void * start_routine(void * arg);
>
> void *arg
>> Sends the arguments to the function. These arguments are casted to void * and need to be casted to the desired type in the function.

Returns:
> On sucess, 0
> Otherwise returns error code(check man pthread_create )

Notes:

## 27.2 Thread Completion
```c
int pthread_join(pthread_t thread, void **retval);
```
Description:
> Waits for thread to terminate and stores in retval the return value. If already terminated returns immediately

Params:
> pthread_t thread
>> Identifier to the thread. For example: pthread_t t1; pthread_join(t1,....);
> 
> void **retval
>> NULL if we dont care about the value
>> Example:
>>
```c
void *returnValue;
pthread_join(t1, &returnValue);
```

Returns:
> On sucess, 0
>
> Otherwise returns error code(check man pthread_create )

Notes:

NEVER return pointers to variables allocated on the thread stack!