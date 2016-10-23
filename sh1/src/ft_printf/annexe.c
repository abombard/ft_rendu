#include "my_printf.h"

int     outdoor(void)
{
  ft_putendl_fd("ft_printf failed", 2);
  return (-1);
}

t_pfun  *init_fun(void)
{
  t_pfun        *ret;

  if (!(ret = (t_pfun *)malloc(sizeof(*ret) * 8)))
    return (NULL);
  ret[0].opt = CHAR;
  ret[0].fun = &case_c;
  ret[1].opt = STRING;
  ret[1].fun = &case_s;
  ret[2].opt = S_INT;
  ret[2].fun = &case_nbr;
  ret[3].opt = US_OCT;
  ret[3].fun = &case_o;
  ret[4].opt = US_DECI;
  ret[4].fun = &case_u;
  ret[5].opt = US_HEX_MIN;
  ret[5].fun = &case_x;
  ret[6].opt = US_HEX_MAJ;
  ret[6].fun = &case_X;
  ret[7].opt = PT;
  ret[7].fun = &case_p;
  return (ret);
}

void    del_pf(t_pf **list)
{
  t_pf    *tmp;

  tmp = *list;
  ft_strdel(&tmp->string);
  ft_strdel(&tmp->arg);
  (*list) = (*list)->next;
  free(tmp);
}

t_pf    *init_list(char *fmt)
{
  t_pf    *list;

  if (!fmt)
    return (NULL);
  list = NULL;
  if (!(list = init_args(fmt)))
    return (NULL);
  init_flags(&list);
  init_opt(&list);
  return (list);
}
