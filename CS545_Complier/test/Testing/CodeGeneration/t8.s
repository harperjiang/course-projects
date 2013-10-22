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
	movl $303,%eax
	movl %ebp,%edx
	addl $8,%edx
	movl (%edx),%edx
	addl $8,%edx
	movl (%edx),%edx
	subl $8,%edx
	movl %eax,(%edx)
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
bar:
	pushl %ebp
	movl %esp,%ebp
	movl $202,%eax
	pushl %eax
	pushl %ebp
	call moo
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
	leal -8(%ebp),%edx
	movl %eax,(%edx)
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	movl $101,%eax
	pushl %eax
	pushl %ebp
	call bar
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
