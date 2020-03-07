#if !STDLIB

#include <stdlib.h>

void *z_memset(void *s, int c, size_t n)
{
	unsigned char *p = s, *e = p + n;
	while (p < e)
		*p++ = c;
	return s;
}

void *z_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *p = src, *e = p + n;
	while (p < e)
		*d++ = *p++;
	return dest;
}

#endif /* !STDLIB */
