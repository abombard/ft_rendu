%define MACH_SYSCALL(nb)	0x2000000 | nb
%define WRITE 				4
	
section .data
hello:
	.string db "Hello world!", 10
	.len equ $ - hello.string

section .text
	global start
	global _main

start:
	call _main
	ret
	
_main:
	push rbp
	mov rbp, rsp
	sub rsp, 16
	mov rdi, 1
	lea rsi, [rel hello.string]
	mov rdx, hello.len
	mov rax, MACH_SYSCALL(WRITE)
	syscall
	leave
	ret
	