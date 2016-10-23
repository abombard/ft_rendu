%define WRITE 1 		; 0x2000004

section .data
msg:		db "(Null)", 10

section .text
	global puts_err
	extern _fat_strlen
	
puts_err:
	cmp rdi, 0
	jz _ret_null
	mov r8, rdi
	call _fat_strlen
	mov r9, rax
	jmp _puts

_puts:
	mov rdi, 2
	mov rsi, r8
	mov rdx, r9
	mov rax, WRITE
	syscall
	cmp rax, 0
	jge _ret_success
	jmp _ret_fail

_ret_null:
	mov rdi, msg
	call puts_err
	jmp _ret_fail

_ret_success:
	mov rdi, r9
	ret

_ret_fail:
	mov rax, -1
	ret
	
