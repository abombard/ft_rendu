;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ret.s                                              :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2015/02/19 17:31:19 by abombard          #+#    #+#              ;
;    Updated: 2015/02/19 17:32:23 by abombard         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

%ifndef RET_S
%define RET_S
	
section .text
	global ret_0
	global ret_1

ret_0:
	mov rax, 0
	ret

ret_1:
	mov rax, 1
	ret

%endif