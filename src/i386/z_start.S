#if !STDLIB
	.text
	.globl	z_start
	.hidden	z_start
	.type	z_start,@function
z_start:
	mov	%esp,	%eax
	push	%edx
	push	%eax
	call	z_entry
	hlt
#endif

