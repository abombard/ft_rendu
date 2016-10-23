;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcat.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 15:36:01 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 16:00:43 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .data
err:	db "strcat: s = Null", 10
	
section .text
	global _fat_strcat
	extern puts_err
	
_fat_strcat:
	cmp rdi, 0
	jz ret_null
	jmp _get_0
	
_get_0:	
	cmp byte[rdi], 0
	jz _cpy
	inc rdi
	jmp _get_0

_cpy:
	cmp byte[rsi], 0
	jz end
	mov rdx, [rsi]
	mov [rdi], rdx
	inc rsi
	inc rdi
	jmp _cpy

ret_null:
	mov rdi, err
	call puts_err
	jmp end
	
end:
	mov byte[rdi], 0
	ret
