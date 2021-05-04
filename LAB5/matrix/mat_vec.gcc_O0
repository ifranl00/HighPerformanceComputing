	.file	"mat_vec.c"
	.text
	.p2align 4
	.globl	mat_vec
	.type	mat_vec, @function
mat_vec:
.LFB39:
	.cfi_startproc
	endbr64
	testl	%ecx, %ecx
	jle	.L1
	movq	%rdi, %r10
	leal	-1(%rcx), %eax
	movslq	%ecx, %rdi
	movq	%rdx, %r8
	salq	$3, %rdi
	leaq	8(%rsi,%rax,8), %r9
	pxor	%xmm2, %xmm2
	xorl	%r11d, %r11d
	.p2align 4,,10
	.p2align 3
.L4:
	movq	$0x000000000, (%r8)
	movq	%rsi, %rax
	movq	%r10, %rdx
	movapd	%xmm2, %xmm1
	.p2align 4,,10
	.p2align 3
.L3:
	movsd	(%rdx), %xmm0
	mulsd	(%rax), %xmm0
	addq	$8, %rax
	addq	%rdi, %rdx
	addsd	%xmm0, %xmm1
	movsd	%xmm1, (%r8)
	cmpq	%r9, %rax
	jne	.L3
	addl	$1, %r11d
	addq	$8, %r8
	addq	$8, %r10
	cmpl	%r11d, %ecx
	jne	.L4
.L1:
	ret
	.cfi_endproc
.LFE39:
	.size	mat_vec, .-mat_vec
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
