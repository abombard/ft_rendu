;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isalpha.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 16:04:54 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 17:47:50 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

section .text
	global _fat_isalpha
	extern ret_0
	extern ret_1
	
_fat_isalpha:
	cmp rdi, 64
	jbe	ret_0
	cmp rdi, 123
	jae ret_0
	cmp rdi, 91
	jae maybe
	jmp ret_1

maybe:
	cmp rdi, 96
	jbe ret_0
	jmp ret_1
