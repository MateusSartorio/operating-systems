	.file	"race_conditions.c"
	.text
	.globl	mails
	.bss
	.align 4
	.type	mails, @object
	.size	mails, 4
mails:
	.zero	4
	.globl	s
	.align 32
	.type	s, @object
	.size	s, 32
s:
	.zero	32
	.globl	named_s
	.align 8
	.type	named_s, @object
	.size	named_s, 8
named_s:
	.zero	8
	.text
	.globl	routine
	.type	routine, @function
routine:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movq	named_s(%rip), %rax
	movq	%rax, %rdi
	call	sem_wait@PLT
	movl	mails(%rip), %eax
	addl	$1, %eax
	movl	%eax, mails(%rip)
	movq	named_s(%rip), %rax
	movq	%rax, %rdi
	call	sem_post@PLT
	addl	$1, -4(%rbp)
.L2:
	cmpl	$99999, -4(%rbp)
	jle	.L3
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	routine, .-routine
	.section	.rodata
.LC0:
	.string	"/cool-semaphore3"
.LC1:
	.string	"mails: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, %edx
	movl	$0, %esi
	leaq	s(%rip), %rax
	movq	%rax, %rdi
	call	sem_init@PLT
	movl	$1, %edx
	movl	$192, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	sem_open@PLT
	movq	%rax, named_s(%rip)
	movl	$0, -28(%rbp)
	leaq	-24(%rbp), %rax
	movl	$0, %ecx
	leaq	routine(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L6
	movl	-28(%rbp), %eax
	jmp	.L11
.L6:
	leaq	-16(%rbp), %rax
	movl	$0, %ecx
	leaq	routine(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L8
	movl	-28(%rbp), %eax
	jmp	.L11
.L8:
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L9
	movl	-28(%rbp), %eax
	jmp	.L11
.L9:
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movl	%eax, -28(%rbp)
	cmpl	$0, -28(%rbp)
	je	.L10
	movl	-28(%rbp), %eax
	jmp	.L11
.L10:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	sem_unlink@PLT
	movq	named_s(%rip), %rax
	movq	%rax, %rdi
	call	sem_close@PLT
	leaq	s(%rip), %rax
	movq	%rax, %rdi
	call	sem_destroy@PLT
	movl	mails(%rip), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
.L11:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
