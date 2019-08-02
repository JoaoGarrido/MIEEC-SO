---
tags:
  - Linux Device Driver 
  - Serial Communication Notes
---

### Seri(Serial Interrupt Mode) char device driver 

Includes:
```c
#include <asm/io.h> //IN and OUT assembly instructions
#include <linux/serial_reg.h> //Contains definitions for the registers
#include <linux/ioport.h> // Functions to reserve I/O port range
```

Reserve I/O port range:
```c
struct resource *request_region(unsigned long first, unsigned long n,const char *name);
void release_region(unsigned long start, unsigned long n);
```

I/O functions:
```c
unsigned inb(unsigned port); //receive byte
void outb(unsigned char byte, unsigned port); //send byte
```

