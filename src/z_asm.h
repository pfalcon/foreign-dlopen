#ifndef Z_ASM_H
#define Z_ASM_H

#define PUBLIC __attribute__((visibility ("default")))
#define PRIVATE __attribute__((visibility ("hidden")))

PRIVATE void z_start(void);
PRIVATE void z_trampo(void (*entry)(void), unsigned long *sp, void (*fini)(void));
PRIVATE long z_syscall(int n, ...);

#endif /* Z_ASM_H */

