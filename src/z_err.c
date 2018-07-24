#include "z_syscalls.h"
#include "z_utils.h"

void z_errx(int eval, const char *fmt, ...)
{
	va_list ap;
	z_fdprintf(2, "error: ");
	va_start(ap, fmt);
	z_vfdprintf(2, fmt, ap);
	va_end(ap);
	z_fdprintf(2, "\n");
	z_exit(eval);
}

