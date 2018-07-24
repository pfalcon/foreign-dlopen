	.text
	.globl	z_syscall
	.type	z_syscall,@function
z_syscall:
	/* Preserve ABI required registers. */
	push	%ebp
	push	%edi
	push	%esi
	push	%ebx
	/* Move arguments to registers. */	
	mov	44(%esp), %ebp
	mov	40(%esp), %edi
	mov	36(%esp), %esi
	mov	32(%esp), %edx
	mov	28(%esp), %ecx
	mov	24(%esp), %ebx
	mov	20(%esp), %eax	/* syscall number */
	/* Jump to kernel, return value comes to eax. */
	int	$0x80
	/* Restore preserved registers. */
	pop	%ebx
	pop	%esi
	pop	%edi
	pop	%ebp
	ret

