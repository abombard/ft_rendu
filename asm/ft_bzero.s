;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_bzero.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 15:34:04 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 16:54:24 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

%define MACH_SYSCALL(nb)	0x2000000 | nb
%define WRITE				4

section .data
err:	db "bzerro : s = Null", 10
	
section .text
	global _fat_bzero
	extern puts_err

_fat_bzero:
	cmp rdi, 0
	jz ret_err
	cmp rsi, 0
	je end
	mov byte[rdi], 0
	dec rsi
	inc rdi
	jmp _fat_bzero

ret_err:
	mov rdi, err
	call puts_err
	ret

end:
	ret

