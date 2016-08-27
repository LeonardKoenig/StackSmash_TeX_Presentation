extern printf

section .text
global function
function:
	; stack layout:
	;
	; [buffer][ret   ][old_bp ][return ]
	push	rbp			; push bp
	mov	rbp, rsp		; update bp

	; ret = (uintptr_t *)(&buffer1[0] + 24);
	lea	rax, [rbp - 0x10]	; load &buffer1[0] into rax
	add	rax, 0x18		; add 3*8, now points to return-address
	mov	[rbp - 0x8], rax	; save result to variable ret

	; (*ret) += 7;
	mov	rax, [rbp - 0x8]	; move ret into rax
	mov	rax, [rax]		; load the return address
	lea	rdx, [rax + 0x7]	; add 7, result into rdx
	mov	rax, [rbp - 0x8]	; move ret into rax again
	mov	[rax], rdx		; write back value

	pop	rbp			; pop bp
	ret

section .data
_fmtstring: db `%d\n`


section .text
global main
main:
	push	rbp			; push bp
	mov	rbp, rsp		; update bp
	sub	rsp, 0x10		; create stack frame

	mov	DWORD [rbp - 0x4], 0x0	; x = 0;
        mov	eax, 0x0	        ; no variadic function
	call	function		; function();
	mov	DWORD [rbp - 0x4], 0x1	; x = 1;

	; printf("d\n",x);
	mov	eax, [rbp - 0x4]	; load x eax
	mov	esi, eax		; move x into esi: 2nd param
	mov	edi, _fmtstring		; load "d\n": 1st param
	mov	eax, 0x0		; clear eax
	call	printf			; call

	; return 0
	mov	eax, 0x0
	leave
	ret

; vim: set ft=nasm et:
