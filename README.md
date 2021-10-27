# psst - Implementing the `ps` command in C

## Why?

- general interest in operating systems class, and C is fun when it does not `SIGSEGV`

## How?

- all processes are under the `/proc` virtual filesystem, from the manpage (`man proc`)

  > The proc filesystem is a pseudo-filesystem which provides an interface to kernel data structures. It is commonly mounted at /proc. Typically, it is mounted automatically by the system

- to get running processes we check the subdirectories with `/proc/[pid]`

  > Each one of these subdirectories contains files and subdirectories exposing information about the process with the corresponding process ID

- using these known paths, and `opendir` to open the `/proc` path and read its contents, we can get the list of running processes

- for each individual process, the details are stored in `/proc/[pid]/stat`, in a specified [format](https://man7.org/linux/man-pages/man5/proc.5.html) 

- we read the contents of the file with a file pointer, load it into a struct with only the properties we need(use?) and display it

## Screenshot
![screenshot of psst](https://i.imgur.com/8ii0cHm.png)

### If you have any reviews about this possibly nasty code, please open an issue. I'm a self proclaimed noob at C.