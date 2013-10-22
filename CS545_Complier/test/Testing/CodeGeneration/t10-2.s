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
	subl $52,%esp
	movl $13,%eax
	leal -4(%ebp),%edx
	movl %eax,(%edx)
	movl $23,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
	movl $33,%eax
	leal -12(%ebp),%edx
	movl %eax,(%edx)
	movl $43,%eax
	pushl %eax
	movl $1,%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -52(%ebp),%edx
	addl %eax,%edx
	popl %eax
	movl %eax,(%edx)
	movl $53,%eax
	pushl %eax
	movl $2,%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -52(%ebp),%edx
	addl %eax,%edx
	popl %eax
	movl %eax,(%edx)
	movl $63,%eax
	pushl %eax
	movl $3,%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -52(%ebp),%edx
	addl %eax,%edx
	popl %eax
	movl %eax,(%edx)
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
