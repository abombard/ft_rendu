
section .text
	global _fat_strdup
	extern malloc
	extern _fat_strlen
	extern _fat_memset
	extern _fat_memcpy
	extern _fat_puts
	
_fat_strdup:
	push rdi
	call _fat_strlen
	mov r9, rax
	mov rdi, r9
	call malloc
	mov rdi, rax
	pop rsi
	mov rdx, r9
	call _fat_memcpy
	mov byte[rdi], 0
	ret
