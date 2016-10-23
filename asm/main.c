#include "asm.h"
#include "libft.h"

int main()
{
	char	s[] = "Les poneys font du ki";
	char	*dst;

	dst = ft_strnew(30);
	ft_strcpy(dst, "yolo ");
	_fat_strcat(dst, s);
	ft_putendl("strcat (dst, Les poneys .., 30) : ");
	ft_putstr("dst = ");
	ft_putendl(dst);
	ft_putstr("s = ");
	ft_putendl(s);

	_fat_bzero(s, 2);
	ft_putstr("bzero (Les poneys font di ki, 2) : ");
	write(1, s, 20);
	ft_putendl("\n");
	
	ft_putstr("isalpha(a) : ");
	ft_putnbr(_fat_isalpha('d'));
	ft_putendl("");
	ft_putstr("isalpha(3) : ");
	ft_putnbr(_fat_isalpha('3'));
	ft_putendl("");

	ft_putstr("isdigit(0) : ");
	ft_putnbr(_fat_isdigit('0'));
	ft_putendl("");
	ft_putstr("isdigit(b) : ");
	ft_putnbr(_fat_isdigit('b'));
	ft_putendl("");

	ft_putstr("isalnum(3) : ");
	ft_putnbr(_fat_isalnum('3'));
	ft_putendl("");
	ft_putstr("isalnum(b) : ");
	ft_putnbr(_fat_isalnum('b'));
	ft_putendl("");
	ft_putstr("isalnum(@) : ");
	ft_putnbr(_fat_isalnum('@'));
	ft_putendl("");

	ft_putstr("isascii($) : ");
	ft_putnbr(_fat_isascii('$'));
	ft_putendl("");
	ft_putstr("isascii(200) : ");
	ft_putnbr(_fat_isascii(200));
	ft_putendl("");

	char s1[] = "yolo";
	ft_putstr("strlen(yolo) : ");
	ft_putnbr(_fat_strlen(s1));
	ft_putendl("");

	int ret;
	ft_putstr("puts(yolo) : ");
	ret = _fat_puts(s1);
	ft_putendl("");
	ft_putstr("ret = ");
	ft_putnbr(ret); ft_putendl("");

	ret = _fat_puts("trying NULL\n");
	ret = _fat_puts(NULL);
	ret = _fat_puts("done\n");

	char *te;
	void *tak;

	te = ft_strdup("Les pones font du ki");
	ft_putstr("memset(Les pones .., 'i', 2) : ");
	tak = _fat_memset(te, 'i', 2);
	ft_putendl("done");
	ft_putendl(te);
	ft_putstr("ret = "); ft_putendl(tak);
	ft_putendl("");
	ft_strdel(&te);

	te = ft_strdup("yolo");
	tak = ft_strdup("     ca sent le jambon");
	tak = _fat_memcpy(tak, te, 4);
	ft_putstr("memcpy(      ca sent le jambon, yolo hey, 4) : ");
	ft_putendl(tak);
	ft_strdel(&te);
	ft_strdel((char**)&tak);

	ft_putstr("strdup(yolo) : ");
	te = _fat_strdup("yolo");
	ft_putendl(te);
	ft_strdel(&te);

	_fat_puts("strlcat : ");
	dst = ft_strnew(30);
	ft_strcpy(dst, "yolo ");
	ft_strcpy(s, "Les poneys font du ki");
	ft_putendl("strlcat (yolo, Les poneys .., 30) : ");
	ft_putstr("ret: ");
	ft_putnbr(_fat_strlcat(dst, s)); ft_putendl("");
	ft_putstr("dst = ");
	ft_putendl(dst);
	ft_putstr("s = ");
	ft_putendl(s);

	return (0);
}
