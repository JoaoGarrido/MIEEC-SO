---
tags:
  - OSTEP
  - Locks
  - Concurrency
  - Chapter 27
  - Chapter 28 
  - Chapter 29
---

# Locks

## 27.3 Locks
To provide mutual exclusion  a critical section we use locks. Locks can be provided by the following functions:

A mutex can be initialized in two ways:
* pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
* pthread_mutex_init(&lock, NULL) followed by pthread_mutex_destroy(&lock) when the lock stops being used 

```c
int pthread_mutex_lock(pthread_mutex_t* mutex);
```

Description:
>  If no other thread holds the lock, the thread will acquire the lock. If another thread does indeed hold the lock,the thread trying to grab the lock will not return from the call until it has acquired the lock.

Params:
> pthread_mutex_t* mutex
>> Example: pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; pthread_mutex_lock(&lock);

```c
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```

Description:
>  Similar to lock(), unlocks if the lock is held.

Params:
> pthread_mutex_t* mutex
>> Example: pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; pthread_mutex_unlock(&lock);

NOTES:
* These functions can fail and return a integer different from 0 if an error occurs

## 28

## 29