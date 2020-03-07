#ifndef FOREIGN_DLOPEN_H
#define FOREIGN_DLOPEN_H

#include "elf_loader.h"

extern void *(*z_dlopen)(const char *filename, int flags);
extern void *(*z_dlsym)(void *handle, const char *symbol);
extern int (*z_dlclose)(void *handle);
extern char *(*z_dlerror)(void);

void init_foreign_dlopen(const char *file);

#endif /* FOREIGN_DLOPEN_H */
