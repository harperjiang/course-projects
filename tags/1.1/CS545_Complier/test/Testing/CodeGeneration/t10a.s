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
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	movl $1,%eax
	pushl %eax
	leal -8(%ebp),%edx
	popl %eax
	movl %eax,(%edx)
label0u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jl label2u
	movl $0,%eax
	jmp label3u
label2u:
	movl $1,%eax
label3u:
	cmpl $1,%eax
	jne label1u
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	subl $1,%eax
	leal -52(%ebp),%edx
	addl %eax,%edx
	popl %eax
	movl %eax,(%edx)
	leal -8(%ebp),%edx
	movl (%edx),%eax
	subl $1,%eax
	leal -52(%ebp),%edx
	addl %eax,%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	movl $1,%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	leal -8(%ebp),%edx
	popl %eax
	movl %eax,(%edx)
	jmp label0u
label1u:
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
