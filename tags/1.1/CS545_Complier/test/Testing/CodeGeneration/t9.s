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
factorial:
	pushl %ebp
	movl %esp,%ebp
	movl $1,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label2u
	movl $0,%eax
	jmp label3u
label2u:
	movl $1,%eax
label3u:
	cmpl $1,%eax
	jne label0u
	movl $1,%eax
	leave
	ret
	jmp label1u
label0u:
	movl $1,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	subl %ebx,%eax
	pushl %eax
	pushl 8(%ebp)
	call factorial
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	leave
	ret
label1u:
	leave
	movl (%esp),%eax
	movl %eax,-4(%ebp)
	leal -4(%ebp),%esp
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	leal -8(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl %ebp
	call factorial
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
