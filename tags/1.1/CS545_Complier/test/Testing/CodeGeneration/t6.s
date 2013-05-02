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
bar:
	pushl %ebp
	movl %esp,%ebp
	leal 20(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leal 16(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leal 12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leave
	movl (%esp),%ebx
	leal 16(%esp),%esp
	movl %ebx,(%esp)
	ret
main:
	pushl %ebp
	movl %esp,%ebp
	subl $12,%esp
	leal -4(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -8(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -12(%ebp),%edx
	pushl %edx
	pushl $intread
	call scanf
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leal -12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl $intwrite
	call printf
	leal -4(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -8(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	leal -12(%ebp),%edx
	movl (%edx),%eax
	pushl %eax
	pushl %ebp
	call bar
	leave
	movl $1,%eax
	movl $0,%ebx
	int $0x80
	ret
.bss
	.lcomm heap,8192
