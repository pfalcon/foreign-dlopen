# ELF loader

A small elf loader. It can load static and dynamically linked ELF EXEC and DYN (pie) binaries. The loader is PIE program that doesn't depend on libc and calls kernel services directly (z_syscall.c).

If the loader needs to load a dynamically linked ELF it places an interpreter (usually ld.so) and a requested binary into a memory and then calls the interpreter entry point.


## Build

Default build is for amd64:

```
$ make
``` 

Build for i386:

```
$ make ARCH=i386
```

Small build (exclude all messages and printf):

```
$ make SMALL=1
```

## Load binaries

Load ls:
```
$ ./loader /bin/ls
```

Load galculator:
```
$ ./loader /usr/bin/galculator
```

