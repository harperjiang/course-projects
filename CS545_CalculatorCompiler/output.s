.text
.globl main
main:
_start:
	movl $5,%eax
	pushl %edx
	mov $heap,%edx
	movl %eax,0(%edx)
	popl %edx
	movl $7,%ebx
	pushl %edx
	mov $heap,%edx
	movl %ebx,4(%edx)
	popl %edx
	movl $3,%ecx
	pushl %edx
	pushl %eax
	movl %ebx,%eax
	movl %ecx,%ebx
	movl $0,%edx
	divl %ebx
	movl %eax,%ebx
	popl %eax
	popl %edx
	addl %ebx,%eax
	pushl %eax
	pushl $1
	call _print
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	pushl %eax
	pushl $1
	call _print
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	movl $6,%ebx
	pushl %edx
	mull %ebx
	popl %edx
	movl $3,%ecx
	addl %ecx,%eax
	movl $9,%edx
	pushl %edx
	mov $heap,%edx
	movl %eax,8(%edx)
	popl %edx
	pushl %edx
	mov $heap,%edx
	movl 4(%edx),%eax
	popl %edx
	pushl %eax
	pushl %edx
	pushl %eax
	popl %edx
	popl %eax
	mull %edx
	movl %eax,%edx
	popl %eax
	pushl %edx
	mov $heap,%edx
	movl %ebx,12(%edx)
	popl %edx
	pushl %edx
	mov $heap,%edx
	movl 8(%edx),%ebx
	popl %edx
	subl %edx,%ebx
	pushl %edx
	mov $heap,%edx
	movl %ecx,16(%edx)
	popl %edx
	movl $4,%ecx
	pushl %ecx
	mov $heap,%ecx
	movl %edx,20(%ecx)
	popl %ecx
	movl $24,%edx
	pushl %edx
	pushl %eax
	movl %ecx,%eax
	mull %edx
	movl %eax,%ecx
	popl %eax
	popl %edx
	addl %ecx,%ebx
	pushl %edx
	mov $heap,%edx
	movl %ebx,0(%edx)
	popl %edx
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	pushl %eax
	pushl $1
	call _print
	pushl %edx
	mov $heap,%edx
	movl 4(%edx),%eax
	popl %edx
	movl $4,%ebx
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%ecx
	popl %edx
	pushl %edx
	pushl %eax
	movl %ebx,%eax
	mull %ecx
	movl %eax,%ebx
	popl %eax
	popl %edx
	addl %ebx,%eax
	pushl %eax
	pushl $1
	call _print
	movl $3,%eax
	movl $6,%ebx
	pushl %edx
	mov $heap,%edx
	movl %ebx,24(%edx)
	popl %edx
	pushl %edx
	mov $heap,%edx
	movl 4(%edx),%ecx
	popl %edx
	pushl %edx
	pushl %eax
	movl %ebx,%eax
	mull %ecx
	movl %eax,%ebx
	popl %eax
	popl %edx
	addl %ebx,%eax
	pushl %eax
	pushl $1
	call _print
	pushl %edx
	mov $heap,%edx
	movl 0(%edx),%eax
	popl %edx
	pushl %eax
	pushl $1
	call _print
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
_print:
	popl %ebx
	popl %eax
	popl %eax
	pushl %ebx
	mov $heap,%ecx
	addl $28,%ecx
	movl $1,%ebx
	cmpl $0,%eax
	jne label0u
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
	jmp label5u
label0u:
	cmpl $0,%eax
	jge label1u
	pushl %edx
	mov $heap,%edx
	movl $45,(%ecx)
	popl %edx
	addl $4,%ecx
	not %eax
	addl $1,%eax
label1u:
	cmpl %ebx,%eax
	jle label2u
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	mull %ebx
	movl %eax,%ebx
	popl %eax
	jmp label1u
label2u:
	cmpl %ebx,%eax
	jge label3u
	pushl %eax
	movl %ebx,%eax
	movl $10,%ebx
	movl $0,%edx
	divl %ebx
	movl %eax,%ebx
	popl %eax
label3u:
	cmpl $0,%eax
	je label4u
	pushl %edx
	movl $0,%edx
	divl %ebx
	addl $48,%eax
	movl %eax,(%ecx)
	movl %edx,%eax
	addl $4,%ecx
	popl %edx
	jmp label2u
label4u:
	cmpl $0,%ebx
	je label5u
	pushl %edx
	mov $heap,%edx
	movl $48,(%ecx)
	popl %edx
	addl $4,%ecx
label5u:
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
	addl $28,%ecx
	popl %edx
	subl %ecx,%edx
	int $0x80
	ret
.bss
	.lcomm heap,8192
