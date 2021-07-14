       .text
       .align  4
       .globl  z_trampo
       .type   z_trampo,%function
z_trampo:
       mov     sp, x1
       mov     x1, x0
       mov     x0, x2
       br      x1
