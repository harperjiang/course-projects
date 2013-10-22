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
moo:
	pushl %ebp
	movl %esp,%ebp
	movl %ebp,%edx
	addl $8,%edx
	movl (%edx),%edx
	subl $4,%edx
	pushl %edx
	pushl $intread
	call scanf
	movl %ebp,%edx
	addl $8,%edx
	movl (%edx),%edx
	subl $4,%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $4,%esp
	movl $0,%eax
	pushl %eax
	pushl %ebp
	call moo
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
