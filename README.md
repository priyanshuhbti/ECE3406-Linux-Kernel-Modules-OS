# Linux Kernel Modules

[![HitCount](http://hits.dwyl.com/Arna-Maity/Linux-Kernel-Modules.svg)](http://hits.dwyl.com/Arna-Maity/Linux-Kernel-Modules)

This repo contains some very basic linux kernel modules to illustrate the basic concepts of kernel programming.

Reference: [The LKM programming Guide](https://www.tldp.org/LDP/lkmpg/2.6/lkmpg.pdf).

1. Basic Hello World Module.
2. Usage of __init & __exit macros.
3. Module Licensing and Documentation.
4. Module Parameters.
5. Simple Character Device Driver.
6. /proc File System Module.
7. /proc using Standard File System.
8. Managing procfs with seq_file.
9. IOCTL (Input/Output ConTroL).

### Tracing syscalls while executing a program:
`strace <prg-name> <args>`

### Some useful StackOverflow Threads:
1. [proc_root](https://stackoverflow.com/questions/2531730/linux-kernel-module-creating-proc-file-proc-root-undeclared-error)
2. [Using newer Kernel APIs](https://devarea.com/linux-kernel-development-creating-a-proc-file-and-interfacing-with-user-space/#.XtSHRhbhWUk)
3. [create_proc_entry() alternative](https://stackoverflow.com/questions/18565381/what-is-alternative-of-create-proc-entry)

### Courses on Basic Linux Kernel Development

1. [A Beginners Guide to Linux Kernel Development](https://training.linuxfoundation.org/training/a-beginners-guide-to-linux-kernel-development-lfd103/) (Linux Foundation)