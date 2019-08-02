---
tags:
  - Linux Device Driver
---

# Linux commands

* cat /proc/devices

  * writes /proc/devices file on the screen with the devices connected and major number

* sudo insmod mod.ko

  * loads kernel module from mod.ko 

* sudo rmmod mod

  * unloads kernel module mod

* lsmod
  
  * shows all modules installed, size and dependencies

* sudo modprobe mod.ko

  * loads kernel module from mod.ko and any other module needed by it

# Notes:

* Splitting modules into multiple layers can reduce complexity (they can be stacked) (Linux Device Drivers, Chapter 2, page 29(48/633) )

*


# API

## (De)Allocating device number

**Theory:**
This functions reserve, register and unregister the device driver on the kernel 

32 bit quantity with 12 bits for major numbers and 20 for minor numbers
```c
dev_t deviceIdentifier
```

Allocates dynamically a range of device numbers (Major and minor numbers can also be statically allocated but that can originate conflicts. Check Linux Device Drivers, Chapter 3, pages 45-49 to use dynamic or static allocation optionally)

Returns:

* Sucess -> 0

* Error -> Negative number 

```c
alloc_chrdev_region(dev_t * dev,unsigned first_minor_number, unsigned number_of_minor_devices, const char* name)
```

Unregister number_of_minor_devices starting from dev
```c
unregister_chrdev_region(dev_t dev, unsigned number_of_minor_devices)
```

Gets major device number from dev_t identifier
```c
MAJOR(dev_t dev)
```

Gets minor device number from dev_t identifier
```c
MINOR(dev_t dev)
```

Gets dev_t identifier from major and minor device numbers
```c
MKDEV(int major, int minor)
```
## Connecting device number to device driver operations

**Theory:**
This functions connect the data structures and functions of the driver with the device number that was previously registered.

After creating the needed variables(file operations and cdev)

**Important data strucutres:**

*structures simplified for the needed use only. More information can be found on Linux Device Drivers, pages 49-55*
* struct file_operations
  * Stores information about the driver functions 
```c
struct file_operations scull_fops = {
  .owner = THIS_MODULE, //pointer to module that holds the structures
  .llseek = scull_llseek, //method to change the current position in a file 
  .read = scull_read, //method to retrieve data from the device
  .write = scull_write, //method to send data to the device
  .ioctl = scull_ioctl, //method for device specific commands 
  .open = scull_open, //method for the first operation to occur on the device file
  .release = scull_release, //method for the last close call to occur on the device file
};
```

* struct file
  * kernel structure that represents an open file descriptor
```c
struct file{
  mode_t f_mode; //FMODE_READ and/or FMODE_WRITE permissions. 
                 //Can be checked in open or ioctl syscall but not needed on read and write because the kernel does that before
  loff_t f_pos; //The current reading/writing position. Should only be changed on llseek, not on read/write
  unsigned int f_flags; //Only O_NONBLOCK and O_SYNC should be checked. Read/Write permissions should be checked using f_mode
  struct file_operations *f_op; //Pointer to the operation that's being executed
  void *private_data; //Normally used to preserve state information across syscalls
  struct dentry *f_dentry; //Used to acess the inode struct by filep->f_dentry->d_inode
};
```

* struct inode
  * kernel structure that represents files(same file can have multiple file descriptors but they all share the same inode struct)
```c
struct inode{
  dev_t i_rdev; //Contains the actual device number
  struct cdev *i_cdev; //Pointer to cdev struct that refers to the char device
};
```

* struct cdev
  * char device structure
```c
struct cdev{
  struct module *owner; //Contains THIS_MODULE
  const struct file_operations *ops; //Contains the address of struct file_operations variable  
  dev_t dev; //Device number
};
```

**Associating the char device with device number:**

There are two ways of initializating a cdev struct:
```c
struct cdev *dev; //global
dev = cdev_alloc();
```
OR
```c
void cdev_init(struct cdev *cdev, struct file_operations *fops);
//Example:
struct cdev dev; //global
cdev_init(&dev, &file_ops);
```
In the 1st case we have a pointer to the struct cdev and in the 2nd case we have the struct cdev previously declared.
After using both methods we have to do some initialization:
```c 
cdev->ops = &file_ops; //only needed on 1st method
//If using the 2nd method, swap -> for .
cdev->owner = THIS_MODULE;
```

After the set up, we need to add the char device to the kernel
```c
int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
```

To remove the char device from the system
```c
void cdev_del(struct cdev *dev);
```

## Open

**Theory:**

Open should be responsible for:
* Check for device-specific errors (such as device-not-ready or similar hardware
problems)
* Initialize the device if it is being opened for the first time
* Update the f_op pointer, if necessary
* Allocate and fill any data structure to be put in filp->private_data

```c
int (*open)(struct inode *inode, struct file *filp);
```

## Release

**Theory:**

Release should be responsible for:
* Deallocate anything that open allocated in filp->private_data
* Shut down the device on last close

```c
int (*release)(struct inode *inode, struct file *filp);
```


## Read

**Theory:**

```c
ssize_t read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
```

```c
unsigned long copy_to_user(void __user *to, const void *from, unsigned long count);
```

## Write

**Theory:**

```c
ssize_t write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);
```
```c
unsigned long copy_from_user(void *to, const void __user *from, unsigned long count);
```



## Memory Functions

```c
void *kmalloc(size_t size, int flags);
```

```c
kzalloc(KERNEL)
```

```c
void kfree(void *ptr);
```


## Utility

This macro calls the init function allocating resources and registering interfaces 
```c
module_init(initialization_function)
```

This macro calls the cleanup function de-allocating resources and uneregistering all interfaces (if the cleanup function is not defined, the kernel does not allow it to be unloaded)
```c
module_exit(cleanup_function)
```

Notes: 
* Initatialization and cleanup functions should be declared static because they are not meant to be visible outside kernel space
* Always allocate before registering! (important because the kernel can start using the module after being registered and if not all the structures are allocated, this can result in race conditions)
* Module code should always check return of functions because even simple memory allocation can fail. 
  * The module should press forward and work even with degraded functionality after the failure. If the failure is critical, the initialization code should unregister the module and free. In the following example we resort to goto statement to handle errors.
  * Another possibilty is to call the cleanup function and de-allocate and unregister the devices and resources that did not fail. This may need extra flags to check the sucess of the initialization code.
```c
int __init my_init_function(void)
{
  int err;
  /* registration takes a pointer and a name */
  err = register_this(ptr1, "skull");
  if (err) goto fail_this;
  err = register_that(ptr2, "skull");
  if (err) goto fail_that;
  err = register_those(ptr3, "skull");
  if (err) goto fail_those;
  return 0; /* success */

  fail_those: unregister_that(ptr2, "skull");
  fail_that: unregister_this(ptr1, "skull");
  fail_this: return err; /* propagate the error */
}
```
 
This macro allows parameters to be sent to the kernel module. More information can be found in Linux Device Drivers, Chapter 2, page 36-37(55/633)
```c
module_param(name_of_variable, type_of_variable, permissions)
```

Kernel function that replaces printf
```c
printk()
```

To export symbols from a module to other modules
```c
EXPORT_SYMBOL(name);
```

Declare module license as GPL
```c
MODULE_LICENSE("GPL");
```

## Includes

Init and cleanup functions
```c
#include <linux/init.h>
```
Symbols and functions definitions needed for loadable modules
```c
#include <linux/module.h>
```
Error codes
```c
#include <linux/errno.h>
```
Flags
```c
#include <linux/fcntl.h>
```
file_operations and file structs
```c
#include <linux/fs.h>
```
cdev structures
```c
#include <linux/cdev.h>,
```
memory functions
```c
#include <linux/slab.h>
```
functions used by the kernel space to move data from and to user space 
```c
#include <asm/uaccess.h>
```
