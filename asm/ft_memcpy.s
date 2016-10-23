section .data
err:	db "memcpy: dst || src = Null", 10

section .text
	global _fat_memcpy
	extern puts_err
	
_fat_memcpy:
	cmp rdi, 0
	jz ret_err
	cmp rsi, 0
	jz ret_err
	mov rcx, rdx
	rep movsb
	mov rax, rdi
	sub rax, rdx
	ret

ret_err:
	mov rdi, err
	call puts_err
	ret
