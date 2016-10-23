section .data
	err db "strlcat: s = Null", 10, 0

section .text
	global _fat_strlcat
	extern _fat_strcat
	extern _fat_strlen
	extern puts_err

_fat_strlcat:
	call _fat_strcat
	call _fat_strlen
	ret
	
