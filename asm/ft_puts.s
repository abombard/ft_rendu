;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_puts.s                                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 18:38:24 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 19:34:22 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

%define WRITE 1 		; 0x2000004

section .data
msg:	db "(Null)", 10
	
section .text
	global _fat_puts
	extern _fat_strlen
	extern puts_err

_fat_puts:
	cmp rdi, 0
	jz _ret_null
	mov r8, rdi
	call _fat_strlen
	mov r9, rax
	jmp _puts
	
_puts:
	mov rdi, 1
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
