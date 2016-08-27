.extern printf

	.text
	.globl	function
function:
	#
	#
	#
	pushq	%rbp
	movq	%rsp, %rbp

	#
	leaq	-16(%rbp), %rax
	addq	$24, %rax
	movq	%rax, -8(%rbp)

	#
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leaq	7(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)

	popq	%rbp
	ret

	.data
.Lfmstring:
	.string	"%d\n"

	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp

	movl	$0, -4(%rbp)
	movl	$0, %eax
	call	function
	movl	$1, -4(%rbp)

	#
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.Lfmstring, %edi
	movl	$0, %eax
	call	printf

	#
	movl	$0, %eax
	leave
	ret

#
