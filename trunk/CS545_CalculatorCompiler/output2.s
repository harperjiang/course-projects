.text
.globl main
main:
	movl $1,%eax
	movl $5,%ebx
	mull %ebx
        movl $-1,%eax
        mull %ebx
        movl $-1,%eax
        imull %ebx
	ret
.bss
	.lcomm heap,8192
