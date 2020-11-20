#include <unistd.h>
#include <dlfcn.h>

#define STR_AND_SIZE(s) s, sizeof(s) - 1

void *funcs[4];

static unsigned long hexstrtoul(const char *s)
{
    unsigned long res = 0;
    char c;
    while ((c = *s++)) {
        if (c >= '0' && c <= '9') {
            c -= '0';
        } else {
            c &= ~0x20;
            c -= 'A' - 0xa;
        }
        res = res << 4 | c;
    }
    return res;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        void (*p)(void*) = (void*)hexstrtoul(argv[1]);
        funcs[0] = dlopen;
        funcs[1] = dlsym;
        funcs[2] = dlclose;
        funcs[3] = dlerror;
        /*printf("Calling to %p (%p %p)\n", p, funcs[0], funcs[1]);*/
        p(funcs);
    } else {
        write(1, STR_AND_SIZE("Success\n"));
    }
}
