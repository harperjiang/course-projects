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
	subl $4,%esp
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	movl $1,%eax
	pushl %eax
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	movl $2,%eax
	popl %ebx
	mull %ebx
	pushl %eax
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -4(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	popl %ebx
	subl %ebx,%eax
	popl %ebx
	addl %ebx,%eax
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
