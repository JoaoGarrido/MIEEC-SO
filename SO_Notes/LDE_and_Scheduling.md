---
tags:
  - OSTEP
  - Processes
  - Scheduling
  - Limited Direct Execution
  - Chapter 6
  - Chapter 7
  - Chapter 8
---

# Limited Direct Execution

The OS must virtualize the CPU in an efficient manner while retaining control over the system.

### 6.1 Basic Technique: Limited Direct Execution
**Control:**

If the OS passed control to the program (Direct Execution), how could we make sure the program was not blocking the OS or acessing data that's not supposed to acess while still running effciently?

**Timesharing:**

The OS must timeshare the processes to keep the system responsive and allow the illusion of multi processing.

## 6.2 Problem #1: Restricited Operations (Control)

To ensure that kernel mantains control over the program is executed in **user mode** and when in this mode can't perform I/O operations and acess memory locations outside it's region.

Although the kernel wants to restrict acess to certain files and memory addresses, the program still needs to perform I/O requests and/or allocate more memory.

To execute restricted operations we need to be in **kernel mode**. When the program wishes to perform some kind of privileged operation resort to **system calls**. 

To be able to perform system calls efficently the OS sets up a trap table(similar to an interrupt table) at boot time.

When program calls a system call, executes a trap instruction assigning a system-call number to a specific register or stack location and saving the registers to kernel stack. This way the kernel is always responsible for the code that's executed when a system call is performed.


<p>
    <img src="./images/LDE_OSTEP.png" width="350" height="450"/>
</p>

## 6.3 Problem #2: Switching Between Processes (Timesharing)

### A Cooperatve Approach: Wait For System Calls

OS trusts the processes of the system to behave reasonably and call yield() sysCall that transfers control to the OS.

Problem -> If the program ends up in a infinite loop (because of a bug or exploit), the system needs reboot

## A Non-Cooperative Apporach: The OS Takes Control

Solution: A timer interrupt that when the interrupt is raised, the currently running process is halted and the OS regains control.

Similarly to when a system call(trap into OS) is executed, the hardware has the responsibility to save the program state when a interrupt occurs. 

## Saving and Restoring Context

Now that the OS has regained control, a decision has to be made: 
* Continue running the currently running process 
* Switch to a different one

This is called **context switch**.

When a context switch occurs some low level assembly code is executed in order to rapidly save the general purprose registers, PC and kernel stack pointer of the running process and then the same registers of the other process are restored. After restoring the information of the now running process, the OS returns from trap instruction and the context switch is complete.

<p>
    <img src="./images/Context_Switch_OSTEP.png" width="350" height="400"/>
</p>

# Scheduling
