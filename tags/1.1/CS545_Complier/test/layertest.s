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
c1:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
b1:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
a1:
	pushl %ebp
	movl %esp,%ebp
	subl $4,%esp
	movl $105,%eax
	leal -4(%ebp),%edx
	movl %eax,(%edx)
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
c2:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	movl %ebp,%edx
	movl 8(%edx),%edx
	movl 8(%edx),%edx
	pushl 8(%edx)
	call a1
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
b2:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	pushl %ebp
	call c2
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
a2:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	movl $300,%eax
	movl %ebp,%edx
	addl $8,%edx
	movl (%edx),%edx
	subl $4,%edx
	movl %eax,(%edx)
	pushl %ebp
	call b2
	leave
	movl (%esp),%ebx
	leal 4(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	pushl %ebp
	call a2
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
