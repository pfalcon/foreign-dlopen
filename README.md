# ELF loader

A small elf loader. It can load static and dynamic linked ELF EXEC and DYN (pie) binaries. The loader doesn't depend on libc and calls kernel services directly (z_syscall.c).

If the loader needs to load dynamic linked ELF it places interpreter binary (usually ld.so) and requested binary into memory then calls the interpreter entry point.

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

