%define READ 0
%define WRITE 1

%assign BUFSIZE 1

section .data
err:	db "U KNO NOTHIN JOHN", 10
	
section .bss
buf:	resb BUFSIZE
	
section .text
	global _fat_cat
	extern _fat_strlen
	extern _fat_puts

_fat_cat:
	push rdi
	jmp read

read:
	pop rdi
	push rdi
	mov rax, READ
	mov rsi, buf
	mov rdx, BUFSIZE
	syscall
	cmp rax, 0
	jl error
	je end
	mov rdi, 1
	mov rsi, buf
	mov rdx, rax
	mov rax, WRITE
	syscall
	jmp read

error:
	mov rdi, err
	call _fat_puts
	ret
	
end:
	mov rdi, 0
	mov rax, 60
	syscall
	ret
