;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_toupper.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 18:32:58 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 18:35:40 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_toupper
	extern ret_0
	extern ret_1

_fat_toupper:
	cmp rdi, 97
	jb ret_0
	cmp rdi, 122
	ja ret_0
	sub rdi, 32
	jmp ret_1