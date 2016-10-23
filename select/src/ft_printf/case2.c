#include "my_printf.h"

char	*case_o(va_list ap, t_pf *node)
{
  char			*tmp;
  unsigned long long	n;

  tmp = NULL;
  if (node->h)
    n = (unsigned short)va_arg(ap, int);
  else if (node->hh)
    n = (unsigned char)va_arg(ap, int);
  else if (node->l)
    n = (unsigned long)va_arg(ap, unsigned long);
  else if (node->ll)
    n = va_arg(ap, unsigned long long);
  else
    n = (unsigned int)va_arg(ap, int);
  if (!(tmp = get_nbr_oct(n)))
    return (NULL);
  return (tmp);
}

char	*case_u(va_list ap, t_pf *node)
{
  char			*tmp;
  unsigned long long	n;

  tmp = NULL;
  if (node->h)
    n = (unsigned short)va_arg(ap, int);
  else if (node->hh)
    n = (unsigned char)va_arg(ap, int);
  else if (node->l)
    n = (unsigned long)va_arg(ap, unsigned long);
  else if (node->ll)
    n = va_arg(ap, unsigned long long);
  else
    n = (unsigned int)va_arg(ap, int);
  if (!(tmp = ft_itoa_ull(n)))
    return (NULL);
  return (tmp);
}

char	*case_x(va_list ap, t_pf *node)
{
  char			*tmp;
  unsigned long long	n;

  tmp = NULL;
  if (node->h)
    n = (unsigned short)va_arg(ap, int);
  else if (node->hh)
    n = (unsigned char)va_arg(ap, int);
  else if (node->l)
    n = (unsigned long)va_arg(ap, unsigned long);
  else if (node->ll)
    n = va_arg(ap, unsigned long long);
  else
    n = (unsigned int)va_arg(ap, int);
  if (!(tmp = get_hex(n)))
    return (NULL);
  return (tmp);
}

char	*case_X(va_list ap, t_pf *node)
{
  char	*tmp;
  int	x;

  (void)node;
  tmp = NULL;
  if (!(tmp = get_hex(va_arg(ap, unsigned int))))
    return (NULL);
  x = 0;
  while (tmp[x])
    {
      tmp[x] = *my_strcapitalize(&tmp[x]);
      x++;
    }
  return (tmp);
}
