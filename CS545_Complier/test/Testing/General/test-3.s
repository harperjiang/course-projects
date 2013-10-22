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
foo:
	pushl %ebp
	movl %esp,%ebp
	leal 16(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl 8(%ebp)
	call foo
	pushl %eax
	leal 16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	jmp label0u
label0u:
	leave
	movl (%esp),%ebx
	leal 12(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl %ebp
	call foo
	leal -4(%ebp),%edx
	movl %eax,(%edx)
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
