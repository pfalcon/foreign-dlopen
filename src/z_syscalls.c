#include <syscall.h>

#include "z_asm.h"
#include "z_syscalls.h"

#if !STDLIB

static int errno;

int *z_perrno(void)
{
	return &errno;
}

static long check_error(long rc)
{
	if (rc < 0 && rc > -4096) {
		errno = -rc;
		rc = -1;
	}
	return rc;
}

#define SYSCALL(name, ...)  check_error(z_syscall(SYS_##name, __VA_ARGS__))
#define DEF_SYSCALL1(ret, name, t1, a1) \
ret z_##name(t1 a1) \
{ \
	return (ret)SYSCALL(name, a1); \
}
#define DEF_SYSCALL2(ret, name, t1, a1, t2, a2) \
ret z_##name(t1 a1, t2 a2) \
{ \
	return (ret)SYSCALL(name, a1, a2); \
}
#define DEF_SYSCALL3(ret, name, t1, a1, t2, a2, t3, a3) \
ret z_##name(t1 a1, t2 a2, t3 a3) \
{ \
	return (ret)SYSCALL(name, a1, a2, a3); \
}

DEF_SYSCALL2(int, open, const char *, filename, int, flags)
DEF_SYSCALL3(ssize_t, read, int, fd, void *, buf, size_t, count)
DEF_SYSCALL3(ssize_t, write, int, fd, const void *, buf, size_t, count)
DEF_SYSCALL1(int, close, int, fd)
DEF_SYSCALL3(int, lseek, int, fd, off_t, off, int, whence)
DEF_SYSCALL1(int, exit, int, status)
DEF_SYSCALL2(int, munmap, void *, addr, size_t, length)
DEF_SYSCALL3(int, mprotect, void *, addr, size_t, length, int, prot)

void *
z_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
#if defined(__i386__)
	/* i386 has old_mmap and mmap2, old_map is a legacy single arg
	 * function, use mmap2 but it needs offset in page units. */
	offset = (unsigned long long)offset >> 12;
	return (void *)SYSCALL(mmap2, addr, length, prot, flags, fd, offset);
#else
	return (void *)SYSCALL(mmap, addr, length, prot, flags, fd, offset);
#endif
}

#endif /* !STDLIB */
