;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 18:59:08 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 19:15:59 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .data
err:	db "strlen: s = Null", 10

section .text
	global _fat_strlen
	extern puts_err
	
_fat_strlen:
	cmp rdi, 0
	jz ret_err
	mov al, 0
	mov cx, -1
	cld
	repnz SCASB
	mov ax, -2
	sub ax, cx
	ret

ret_err:
	mov rdi, err
	call puts_err
	ret
