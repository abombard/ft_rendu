;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isdigit.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 16:32:27 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 17:47:30 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_isdigit
	extern ret_0
	extern ret_1
	
_fat_isdigit:
	cmp	rdi, 48
	jb ret_0
	cmp rdi, 57
	ja ret_0
	jmp ret_1
