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
	leal -4(%ebp),%edx
	pushl %edx
	pushl $realread
	call scanf
	leal -4(%ebp),%edx
	flds (%edx)
	leal -4(%ebp),%edx
	flds (%edx)
	fmulp
	fld1
	fsubrp
	leal -8(%ebp),%edx
	fstps (%edx)
	leal -8(%ebp),%edx
	flds (%edx)
	leal -4(%ebp),%edx
	flds (%edx)
	fld1
	fsubrp
	fdivrp
	movl $0x4048f5c3, %eax
	subl $4,%esp
	movl %eax,(%esp)
	flds (%esp)
	addl $4,%esp
	faddp
	leal -12(%ebp),%edx
	fstps (%edx)
	leal -12(%ebp),%edx
	flds (%edx)
	subl $8,%esp
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
