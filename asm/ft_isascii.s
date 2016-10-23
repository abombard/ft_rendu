;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isascii.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 17:44:10 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 18:27:50 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_isascii
	extern ret_0
	extern ret_1

_fat_isascii:
	cmp rdi, 0
	jb ret_0
	cmp rdi, 127
	ja ret_0
	jmp ret_1