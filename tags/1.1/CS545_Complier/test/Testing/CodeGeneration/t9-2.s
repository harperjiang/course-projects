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
gcd:
	pushl %ebp
	movl %esp,%ebp
	movl $0,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	je label2u
	movl $0,%eax
	jmp label3u
label2u:
	movl $1,%eax
label3u:
	cmpl $1,%eax
	jne label0u
	leal 16(%ebp),%edx
	movl (%edx),%eax
	leave
	ret
	jmp label1u
label0u:
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal 16(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	movl $0,%edx
	divl %ebx
	movl %edx,%eax
	pushl %eax
	pushl 8(%ebp)
	call gcd
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
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -8(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl %ebp
	call gcd
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
