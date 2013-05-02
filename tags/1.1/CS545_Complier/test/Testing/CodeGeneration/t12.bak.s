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
	subl $12,%esp
	movl $0x4048f5c3, %eax
	movl %eax, 8(%esp)
	flds 8(%esp)
	subl $4,%esp
	fstpl (%esp)
	pushl $realwrite
	call printf
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
