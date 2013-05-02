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
	subl $48,%esp
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	movl $1,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
label0u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
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
	jne label1u
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	mull %ebx
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -48(%ebp),%edx
	addl %eax,%edx
	popl %eax
	movl %eax,(%edx)
	movl $1,%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
	jmp label0u
label1u:
	movl $1,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
label4u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label6u
	movl $0,%eax
	jmp label7u
label6u:
	movl $1,%eax
label7u:
	cmpl $1,%eax
	jne label5u
	leal -8(%ebp),%edx
	movl (%edx),%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -48(%ebp),%edx
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
	leal -8(%ebp),%edx
	movl %eax,(%edx)
	jmp label4u
label5u:
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
