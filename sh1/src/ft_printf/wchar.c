#include "my_printf.h"

int	size_bin(unsigned int n)
{
  long	nb;
  int	ret;

  ret = 0;
  nb = n;
  if (nb < 0)
    nb = -nb;
  while (nb >= 2)
    {
      nb /= 2;
      ret += 1;
    }
  return (ret);
}

char	*get_spec(unsigned int ch, int size, char *tmp)
{
  if (size < 12)
    {
      tmp[0] = (6 << 5) | (((ch >> 6) << 27) >> 27);
      tmp[1] = (2 << 6) | ((ch << 26) >> 26);
      tmp[2] = 0;
    }
  else if (size < 17)
    {
      tmp[0] = (14 << 4) | (((ch >> 12) << 28) >> 28);
      tmp[1] = (2 << 6) | (((ch >> 6) << 26) >> 26);
      tmp[2] = (2 << 6) | ((ch << 26) >> 26);
      tmp[3] = 0;
    }
  else
    {
      tmp[0] = (30 << 3) | (((ch >> 18) << 29) >> 29);
      tmp[1] = (2 << 6) | (((ch >> 12) << 26) >> 26);
      tmp[2] = (2 << 6) | (((ch >> 6) << 26) >> 26);
      tmp[3] = (2 << 6) | ((ch << 26) >> 26);
      tmp[4] = 0;
    }
  return (tmp);
}

char	*get_wchar(unsigned int ch)
{
  char	*tmp;
  int	size;

  size = size_bin(ch);
  if (!(tmp = ft_strnew(5)))
    return (NULL);
  if (size < 8)
    {
      tmp[0] = (unsigned char)ch;
      tmp[1] = 0;
    }
  else
    tmp = get_spec(ch, size, tmp);
  return (tmp);
}

char	*case_s(va_list ap, t_pf *node)
{
  char		*ret;
  char		*tmp;
  unsigned int	*wc;
  int		x;

  (void)node;
  ret = NULL;
  tmp = NULL;
  if (node->l)
    {
      wc = (unsigned int *)va_arg(ap, wchar_t *);
      x = -1;
      while (wc[++x])
	{
	  tmp = get_wchar(wc[x]);
	  ret = my_stradd(&ret, tmp, 0);
	  ft_strdel(&tmp);
	}
    }
  else
    ret = ft_strdup(va_arg(ap, char *));
  if (ret == NULL)
    ret = ft_strdup("(null)");
  return (ret);
}

char	*case_c(va_list ap, t_pf *node)
{
  char		*tmp;
  unsigned int	ch;

  (void)node;
  tmp = NULL;
  ch = va_arg(ap, unsigned int);
  tmp = get_wchar(ch);
  return (tmp);
}
