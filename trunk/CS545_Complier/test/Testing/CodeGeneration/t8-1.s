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
alpha:
	pushl %ebp
	movl %esp,%ebp
	movl $42,%eax
	movl %ebp,%edx
	addl $8,%edx
	movl (%edx),%edx
	addl $8,%edx
	movl (%edx),%edx
	subl $12,%edx
	movl %eax,(%edx)
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
beta:
	pushl %ebp
	movl %esp,%ebp
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl 8(%ebp)
	call alpha
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
middle:
	pushl %ebp
	movl %esp,%ebp
	movl $0,%eax
	pushl %eax
	pushl %ebp
	call beta
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	movl $0,%eax
	leal -12(%ebp),%edx
	movl %eax,(%edx)
	movl $5,%eax
	pushl %eax
	pushl %ebp
	call middle
	leal -12(%ebp),%edx
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
