	.text
	.align	4
	.globl	z_trampo
	.type	z_trampo,%function
z_trampo:
	mov	sp, r1
	mov	r1, r0
	mov	r0, r2
	bx	r1
