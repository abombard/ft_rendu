#include "libft.h"

char	*my_stradd(char **s1, char **s2, int len)
{
  char	*ret;
  int	length;

  ret = NULL;
  if (s2)
    {
      length = s1 ? ft_strlen(*s1) + ft_strlen(*s2) : ft_strlen(*s2);
      ret = ft_strnew(length + 1);
      if (s1)
	ft_strlcat(ret, *s1, ft_strlen(*s1) + 1);
      len += 1;
      ft_strlcat(ret, *s2, s1 ? ft_strlen(*s1) + len : len);
      ft_strdel(s1);
    }
  return (ret);
}
