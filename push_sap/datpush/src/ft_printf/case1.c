#include "my_printf.h"
#include <inttypes.h>

char	*case_nbr(va_list ap, t_pf *node)
{
  char		*tmp;
  long long	n;

  tmp = NULL;
  if (node->j)
    n = (intmax_t)va_arg(ap, int);
  else if (node->z)
    n = (size_t)va_arg(ap, int);
  else if (node->h)
    n = (short)va_arg(ap, int);
  else if (node->hh)
    n = (char)va_arg(ap, int);
  else if (node->l)
    n = (long)va_arg(ap, long);
  else if (node->ll)
    n = va_arg(ap, long long);
  else
    n = (int)va_arg(ap, int);
  if (!(tmp = ft_itoa_lg(n)))
    return (NULL);
  return (tmp);
}

char	*case_p(va_list ap, t_pf *node)
{
  char		*tmp;
  unsigned long	pt;

  (void)node;
  tmp = NULL;
  pt = va_arg(ap, unsigned long);
  if (pt == 0)
    {
      if (!(tmp = ft_strdup("(nil)")))
	return (NULL);
    }
  else if (!(tmp = get_nbr_hex(pt)))
    return (NULL);
  return (tmp);
}
