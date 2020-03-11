# foreign-dlopen

## Intro

Calling dlopen() function from statically-linked binaries is a well-known
(in narrow circles) problem [*](#references). A common approach is not
supporting it at all. A usual explanation goes along the lines of:

1. You usually link statically to exclude unneeded functions from the binary.
2. But if you want to dynamically load a shared library, it likely itself
is linked dynamically against libc (doing otherwise requires extra legwork,
and if you have a few such shared libraries, themselves statically linked,
you duplicate code in each).
3. But that means you would need to carry around (big) libc.so, which
undermines the original idea of static linking (you could link your app
against dynamic libc and save space).
4. Alternatively, you could link entire libc into your static executable,
and export dynamic symbols (`ld --export-dynamic`). That avoids carriying
around extra libc.so file, but again requires extra legwork. And it still
undermines the original benefit of static linking, as your app will be
the size of libc.so (+ your app's code).

The summary is that if you want to use dlopen() from static binary,
you would need to do extra legwork, and would lose benefits of static
linking. Ergo, don't use dlopen() with static linking, use dynamic linking
instead! And as no reasonable person would use dlopen() with static linking,
let's remove dlopen() (and that's entire dynamic loader, quite a bloaty
piece of code!) support from statically linked libc, to let people who really
need static linking, reap the maximum benefits of it.

Those are all very valid arguments, but they are all based on a "plugin"
model: you have a common system, sharing a common libc.

That's not the only usage model though. There's another model, which we'll
call "FFI (Foreign Function Interface) model". It goes along the lines of:

1. Suppose you have a perfect, closed world application. Statically linked
of course.
2. But you want to go out to ~~dirty~~ bustling outside world (in other
words, let your application, or users of your appplication, to dlopen()
outside shared libraries).
3. There're absolutely no expectations or stipulations about which libc
is used by those shared libraries. In particular, there's no expectations
that libc of your application and external shared lib are the same. Or
that you know which libc is used by external lib at all. For example,
your static binary may be linked against musl libc, but you may want
to load (allow to load) glibc bloat lying in abundance on a typical Linux
system.

Again, the only thing you want is to maintain your static perfect world,
independent from outside hustle. But, at user discretion, you want to
allow this hustling outside world into your address space, by means of
dlopen().

This cute project is a proof-of-concept solution for this usecase.

### References

* https://www.openwall.com/lists/musl/2012/12/08/4

## Details

Implementation idea #1: a (custom) ELF loader. Problem: trying to implement
"full" ELF loader (recursively load dependent .so, etc.) is prolematic, e.g.
because glibc (libc.so) is tightly coupled with dynamic loader aka interpreter
(ld.so). If you just load libc.so, and its dependency ld.so, a lot of
stuff in ld.so will remain uninitialized, then libc.so will call into ld.so,
which will crash. To properly initialize ld.so, it must be "run", i.e.
execution should go into its entry point (and not just ELF INIT func). But
when started that way, ld.so loads an executable, which then terminates.

Idea #2: Make ld.so load an executable which will jump back into our custom
loader. This way, both ld.so will be initialized, and we get back control.
Coupled with setjmp/longjmp, this can be turned into a reusable library.
Its structure is:

1. Custom ELF loader, built against any libc or lack thereof. This should be
simplified loader, without support for loading shared libs, etc. The only
thing it needs to load is a "helper" target executable and its INTERP.
2. It calls into INTERP, the call wrapped with `setjmp`. The corresponding
`longjmp` is wrapped into a global func, whose address (in ascii) we pass as
a command-line argument to the "helper" target binary.
3. The "helper" binary should be linked against native libc of the target
environment whose shared libs we want to load (e.g., glibc).
4. Target binary is also linked agains target libc's libdl. The binary captures
addresses of dlopen()/dlsym()/etc. funcs into an array, and performs function
call into the address passed as a command-line arg, passing array as a
function arg.
5. That address is, as mentioned above, is a function which performs `longjmp`,
after storing the passed `dlopen()`, etc. function addresses for future use.
6. After longjmp, we're back to our application, which now has access to
`dlopen()`, etc. of the target system.

## Building and running

1. `cd src`
2. Build target helper executable: `make -f Makefile.fdlhelper`. As explained
above, it should be built against target system from which you want to load
shared libs dynamically using dlopen(). (If you build this on a typical Linux
system, it will be built against glibc.)
3. Build static, stdlib-less sample application: `make STDLIB=0`. (You must
pass `STDLIB=0` for full effect. By default, the sample is built against
stdlib, which is helpful during development/debugging.)
4. Run the sample: `./foreign_dlopen_demo`. While it is static, it will
dynamically load libc.so.6 and call printf() from it. (All this using
`fdlhelper` executable built in a previous step.)

## Credits

"Foreign dlopen" idea and implementation is by Paul Sokolovsky. The
implementation is based on the ELF loader by Mikhail Ilyin:
https://github.com/MikhailProg/elf , the original README of that project
follows.

---

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

