.data
intwrite:
	.string "%d\n"
intread:
	.string "%d"
realwrite:
	.string "%f\n"
realread:
	.string "%f"
.text
.globl main
main:
	pushl %ebp
	movl %esp,%ebp
	subl $24,%esp
	movl $2,%eax
	leal -16(%ebp),%edx
	movl %eax,(%edx)
	movl $1,%eax
	leal -20(%ebp),%edx
	movl %eax,(%edx)
	movl $3,%eax
	leal -24(%ebp),%edx
	movl %eax,(%edx)
	leal -24(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -20(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	pushl %eax
	leal -24(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -20(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -24(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -20(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	pushl %eax
	leal -24(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -20(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	popl %ebx
	addl %ebx,%eax
	popl %ebx
	mull %ebx
	leal -4(%ebp),%edx
	movl %eax,(%edx)
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192