;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_tolower.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 18:36:24 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 18:38:00 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_tolower
	extern ret_0
	extern ret_1

_fat_tolower:
	cmp rdi, 65
	jb ret_0
	cmp rdi, 90
	ja ret_0
	add rdi, 32
	jmp ret_1