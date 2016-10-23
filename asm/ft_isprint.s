;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isprint.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 18:28:33 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 18:31:14 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_isprint
	extern ret_0
	extern ret_1

_fat_isprint:
	cmp rdi, 33
	jb ret_0
	cmp rdi, 126
	ja ret_0
	jmp ret_1