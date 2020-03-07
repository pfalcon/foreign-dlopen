#include "foreign_dlopen.h"
#include "elf_loader.h"
#include "z_utils.h"
#include <setjmp.h>

jmp_buf jmpbuf;
char addrbuf[17];
void *(*z_dlopen)(const char *filename, int flags);
void *(*z_dlsym)(void *handle, const char *symbol);
int (*z_dlclose)(void *handle);
char *(*z_dlerror)(void);

void do_jump(void **p)
{
	z_printf("do_jump: %p\n", p);
	z_dlopen = p[0];
	z_dlsym = p[1];
	z_dlclose = p[2];
	z_dlerror = p[3];
	longjmp(jmpbuf, 1);
}

void init_foreign_dlopen(const char *file)
{
	char *argv[2];
	z_sprintn(addrbuf, (unsigned long)do_jump, 16);
	argv[0] = (char *)file;
	argv[1] = addrbuf;

	if (!setjmp(jmpbuf)) {
		exec_elf(file, 2, argv);
	} else {
		return;
	}
}
