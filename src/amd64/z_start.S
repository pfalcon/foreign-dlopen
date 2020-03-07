#if !STDLIB
	.text
	.align	4
	.globl	z_start
	.hidden	z_start
	.type	z_start,@function
z_start:
	mov	%rsp,	%rdi
	mov	%rdx,	%rsi
	call	z_entry
	hlt
#endif

