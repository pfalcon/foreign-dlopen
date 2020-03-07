#ifndef Z_SYSCALLS_H
#define Z_SYSCALLS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <fcntl.h>
#include <unistd.h>

#if STDLIB

#define z_exit _exit
#define z_open open
#define z_close close
#define z_lseek lseek
#define z_read read
#define z_write write
#define z_mmap mmap
#define z_munmap munmap
#define z_mprotect mprotect

#else

#define z_errno	(*z_perrno())

int	z_exit(int status);
int	z_open(const char *pathname, int flags);
int	z_close(int fd);
int	z_lseek(int fd, off_t offset, int whence);
ssize_t	z_read(int fd, void *buf, size_t count);
ssize_t	z_write(int fd, const void *buf, size_t count);
void	*z_mmap(void *addr, size_t length, int prot,
		int flags, int fd, off_t offset);
int	z_munmap(void *addr, size_t length);
int	z_mprotect(void *addr, size_t length, int prot);
int	*z_perrno(void);

#endif /* STDLIB */

#endif /* Z_SYSCALLS_H */
