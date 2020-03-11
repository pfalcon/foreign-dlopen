#include "z_utils.h"
#include "z_syscalls.h"
#include "foreign_dlopen.h"

#define RTLD_NOW 0x0002

int main(int argc, char *argv[])
{
	(void)argc;

	init_exec_elf(argv);

	init_foreign_dlopen("fdlhelper");

	z_printf("Come back: dlopen=%p\n", z_dlopen);
	void *h = z_dlopen("libc.so.6", RTLD_NOW);
	z_printf("Handle of libc.so.6: %p\n", h);
	void *p = z_dlsym(h, "printf");
	int (*_printf)(const char *fmt, ...) = p;
	z_printf("Next line is printed by the printf() from libc.so:\n\n");
	_printf("Hello from the other side!\n");

	void *h2 = z_dlopen("libz.so.1", RTLD_NOW);
	z_printf("\nHandle of libz.so.1: %p\n", h2);

	z_exit(0);
}
