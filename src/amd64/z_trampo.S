	.text
	.align	4
	.globl	z_trampo
	.type	z_trampo,@function
z_trampo:
	mov	%rsi,	%rsp
	jmp	*%rdi
	/* Should not reach. */
	hlt

