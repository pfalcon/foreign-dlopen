	.text
	.globl	z_trampo
	.type	z_trampo,@function
z_trampo:
	mov	4(%esp), %eax
	mov	8(%esp), %ecx
	mov	12(%esp), %edx
	mov	%ecx, %esp
	jmp	*%eax
	/* Should not reach. */
	hlt

