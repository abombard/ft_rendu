#ifndef ASM_H
#define ASM_H

#include "libft.h"

void		_fat_cat(int fd);
char		*_fat_strdup(char *s);
void		*_fat_memcpy(char *dst, char *src, size_t n);
void		*_fat_memset(char *s, int c, size_t n);
int		fat_puts(char *s);
int		fat_strlen(char *s);
int		fat_isascii(int c);
int		fat_isalnum(int c);
int		fat_isdigit(int c);
int		fat_isalpha(int c);
void	fat_strcat(char *s1, char *s2);
void	fat_bzero(char *s, size_t len);

#endif
