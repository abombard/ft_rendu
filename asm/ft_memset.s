section .data
err:	db "memset: dst = Null || n <= 0", 10

section .text
	global _fat_memset
	extern puts_err

_fat_memset:
	cmp rdi, 0
	jz ret_err
	cmp rdx, 0
	jle err
	lea rax, [rsi]
	mov rcx, rdx
	cld
	rep stosb
	lea rax, [rdi]
	sub rax, rdx
	ret

ret_err:
	mov rdi, err
	call puts_err
	ret
