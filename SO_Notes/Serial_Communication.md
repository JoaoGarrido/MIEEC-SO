---
tags:
  - Linux Device Driver
  - Serial Communication Notes
---

# Serial Port Device Driver

## Common Notes and advices

### **usocat**

To exchange data between the host and guest OS we normally use the socat utility.

There is a simpler utility, usocat, that is minimal and only supports communication via Unix domain sockets.

**To send data from the stdin of the host OS via the serial port to the VM we use:**
```sh
./usocat - /tmp/vbox_ser_port1
```
**To send data from the stdin of the VM via the serial port to the host machine we use on the host OS:**
```sh
./usocat /tmp/vbox_ser_port1 -
```
and then on the guest OS:
```sh
cat < /dev/ttyS0
```

To buffer the data(Only valid from host to guest):
```sh
./usocat -b - /tmp/vbox_ser_port1
```

### Disabling the standard serial port
We want to use our device driver and not the standard one.

To disabled it we use a kernel module and a script. The standard serial device driver can't be used until the system is rebooted.

To run:
```sh
sudo bash ./disableserial.sh
```

### Basic Serp(Serial Polled Mode) char device driver 

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

