;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isalnum.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 16:41:01 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 18:10:12 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_isalnum
	extern _fat_isalpha
	extern _fat_isdigit
	extern ret_0
	extern ret_1
	
_fat_isalnum:
	call _fat_isalpha
	cmp rax, 1
	je ret_1
	jmp _fat_isdigit
