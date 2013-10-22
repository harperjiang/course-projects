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
	movl $10,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	movl $0,%edx
	divl %ebx
	jmp label0u
label0u:
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl %ebp
	call foo
	leal -8(%ebp),%edx
	movl %eax,(%edx)
	leal -8(%ebp),%edx
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
