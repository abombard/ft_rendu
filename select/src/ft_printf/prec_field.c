#include "my_printf.h"

char	*field_bfore(int len, char *t, char c)
{
  char	*ret;
  int	x;

  ret = NULL;
  ret = ft_memalloc(len + ft_strlen(t) + 1);
  ret = ft_strcpy(ret, t);
  x = 0;
  while (ret[x])
    x++;
  while (x < len + ft_strlen(t))
    ret[x++] = c;
  ret[x] = 0;
  return (ret);
}

char	*field_after(int len, char *t, char c, t_pf *node)
{
  int	x;
  char	*ret;

  ret = NULL;
  x = 0;
  if (!(ret = ft_strnew(node->field + 1)))
    return (NULL);
  x = 0;
  while (len)
    {
      ret[x] = c;
      x++, len--;
    }
  ft_strcpy(&ret[x], t);
  return (ret);
}

char	*field_width(char *t, t_pf *node)
{
  char	*ret;
  int	len;
  char	c;

  ret = NULL;
  if (node->zero && (!node->moins || !node->field))
    c = '0';
  else
    c = ' ';
  len = node->field - ft_strlen(t);
  if (node->opt == PT && c == '0')
    len -= 2;
  if (node->moins && len > 0)
    {
      ret = field_bfore(len, t, c);
    }
  else if (len > 0)
    {
      ret = field_after(len, t, c, node);
    }
  return (ret);
}

char	*precision(char *t, t_pf *node, int opt)
{
  char	*ret;
  int	len;
  int	x;

  ret = NULL;
  if (opt == S_INT || opt == US_HEX_MAJ || opt == US_HEX_MIN \
      || opt == US_OCT || opt == PT)
    {
      len = node->precision - ft_strlen(t);
      if (len > 0)
	{
	  if (!(ret = ft_strnew(node->precision + 1)))
	    return (NULL);
	  x = 0;
	  while (x < len)
	    ret[x++] = '0';
	  ft_strcpy(&ret[x], t);
	}
    }
  return (ret);
}
