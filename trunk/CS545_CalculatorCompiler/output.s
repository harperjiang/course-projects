.text
.globl main
main:
	movl $1,%eax
	pushl %eax
	movl $5,%eax
	popl %ebx
	subl %eax,%ebx
	movl %ebx,%eax
	pushl %edx
	mov $heap,%edx
	movl %eax,0(%edx)
	popl %edx
	nop
	movl $4,%eax
	pushl %eax
	movl $6,%eax
	popl %ebx
	addl %eax,%ebx
	movl %ebx,%eax
	pushl %edx
	mov $heap,%edx
	movl %eax,4(%edx)
	popl %edx
	nop
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	pushl %eax
	pushl %edx
	mov $heap,%edx
	movl 4(%edx),%eax
	popl %edx
	popl %ebx
	pushl %ebx
	pushl %ebx
	pushl %eax
	popl %ebx
	popl %eax
	mull %ebx
	popl %ebx
	movl %eax,%ebx
	movl %ebx,%eax
	mov $heap,%ecx
	addl $8,%ecx
	movl $1,%ebx
	cmpl $0,%eax
	jne label0
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
	jmp label5
label0:
	cmpl $0,%eax
	jge label1
	pushl %edx
	mov $heap,%edx
	movl $45,(%ecx)
	popl %edx
	addl $4,%ecx
	not %eax
	addl $1,%eax
label1:
	cmpl %ebx,%eax
	jle label2
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	mull %ebx
	movl %eax,%ebx
	popl %eax
	jmp label1
label2:
	cmpl %ebx,%eax
	jge label3
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	movl $0,%edx
	divl %ebx
	movl %eax,%ebx
	popl %eax
label3:
	cmpl $0,%eax
	je label4
	pushl %edx
	movl $0,%edx
	divl %ebx
	addl $48,%eax
	movl %eax,(%ecx)
	movl %edx,%eax
	addl $4,%ecx
	popl %edx
	jmp label2
label4:
	cmpl $0,%ebx
	je label5
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
label5:
	movl $4,%eax
	movl $1,%ebx
	pushl %edx
	mov $heap,%edx
	movl $13,(%ecx)
	popl %edx
	addl $4,%ecx
	pushl %edx
	mov $heap,%edx
	movl $10,(%ecx)
	popl %edx
	addl $4,%ecx
	pushl %ecx
	mov $heap,%ecx
	addl $8,%ecx
	popl %edx
	subl %ecx,%edx
	int $0x80
	nop
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	pushl %eax
	pushl %edx
	mov $heap,%edx
	movl 4(%edx),%eax
	popl %edx
	popl %ebx
	pushl %ebx
	pushl %ebx
	pushl %eax
	popl %ebx
	popl %eax
	mull %ebx
	popl %ebx
	movl %eax,%ebx
	movl %ebx,%eax
	pushl %edx
	mov $heap,%edx
	movl %eax,8(%edx)
	popl %edx
	nop
	movl $5,%eax
	pushl %eax
	movl $8,%eax
	popl %ebx
	subl %eax,%ebx
	movl %ebx,%eax
	pushl %edx
	mov $heap,%edx
	movl %eax,12(%edx)
	popl %edx
	nop
	pushl %edx
	mov $heap,%edx
	movl 8(%edx),%eax
	popl %edx
	pushl %eax
	pushl %edx
	mov $heap,%edx
	movl 12(%edx),%eax
	popl %edx
	popl %ebx
	subl %eax,%ebx
	movl %ebx,%eax
	mov $heap,%ecx
	addl $16,%ecx
	movl $1,%ebx
	cmpl $0,%eax
	jne label6
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
	jmp label11
label6:
	cmpl $0,%eax
	jge label7
	pushl %edx
	mov $heap,%edx
	movl $45,(%ecx)
	popl %edx
	addl $4,%ecx
	not %eax
	addl $1,%eax
label7:
	cmpl %ebx,%eax
	jle label8
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	mull %ebx
	movl %eax,%ebx
	popl %eax
	jmp label7
label8:
	cmpl %ebx,%eax
	jge label9
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	movl $0,%edx
	divl %ebx
	movl %eax,%ebx
	popl %eax
label9:
	cmpl $0,%eax
	je label10
	pushl %edx
	movl $0,%edx
	divl %ebx
	addl $48,%eax
	movl %eax,(%ecx)
	movl %edx,%eax
	addl $4,%ecx
	popl %edx
	jmp label8
label10:
	cmpl $0,%ebx
	je label11
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
label11:
	movl $4,%eax
	movl $1,%ebx
	pushl %edx
	mov $heap,%edx
	movl $13,(%ecx)
	popl %edx
	addl $4,%ecx
	pushl %edx
	mov $heap,%edx
	movl $10,(%ecx)
	popl %edx
	addl $4,%ecx
	pushl %ecx
	mov $heap,%ecx
	addl $16,%ecx
	popl %edx
	subl %ecx,%edx
	int $0x80
	nop
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
