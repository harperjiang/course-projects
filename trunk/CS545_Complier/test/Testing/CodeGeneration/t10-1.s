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
	movl $1,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label3u
	movl $0,%eax
	jmp label4u
label3u:
	movl $1,%eax
label4u:
	cmpl $1,%eax
	jne label1u
	movl $1,%eax
	jmp label0u
	jmp label2u
label1u:
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	movl $1,%eax
	pushl %eax
	leal 12(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	subl %ebx,%eax
	pushl %eax
	pushl 8(%ebp)
	call foo
	popl %ebx
	mull %ebx
	jmp label0u
label2u:
label0u:
	leave
	movl (%esp),%ebx
	leal 8(%esp),%esp
	movl %ebx,(%esp)
	ret
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
label5u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label7u
	movl $0,%eax
	jmp label8u
label7u:
	movl $1,%eax
label8u:
	cmpl $1,%eax
	jne label6u
	leal -8(%ebp),%edx
	movl (%edx),%eax
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
	jmp label5u
label6u:
	movl $1,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
label9u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label11u
	movl $0,%eax
	jmp label12u
label11u:
	movl $1,%eax
label12u:
	cmpl $1,%eax
	jne label10u
	movl $1,%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	subl $1,%eax
	movl $4,%ebx
	mull %ebx
	leal -48(%ebp),%edx
	addl %eax,%edx
	movl (%edx),%eax
	popl %ebx
	addl %ebx,%eax
	pushl %eax
	pushl %ebp
	call foo
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
	jmp label9u
label10u:
	movl $1,%eax
	leal -8(%ebp),%edx
	movl %eax,(%edx)
label13u:
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	popl %ebx
	cmpl %ebx,%eax
	jle label15u
	movl $0,%eax
	jmp label16u
label15u:
	movl $1,%eax
label16u:
	cmpl $1,%eax
	jne label14u
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
	jmp label13u
label14u:
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
