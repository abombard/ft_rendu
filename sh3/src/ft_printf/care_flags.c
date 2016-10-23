#include "my_printf.h"

char    *diez(char *t, int opt)
{
  char    *ret;

  ret = NULL;
  if (!ft_strcmp(t, "(nil)") || !ft_strcmp(t, "(Null)")
      || !ft_strcmp(t, "0"))
    return (NULL);
  if (opt == US_OCT)
    ret = ft_strjoin("0", t);
  else if (opt == US_HEX_MIN || opt == PT)
    ret = ft_strjoin("0x", t);
  else if (opt == US_HEX_MAJ)
    ret = ft_strjoin("0X", t);
  return (ret);
}

char    *spaceplus(char *t, t_pf *node)
{
  char    *ret;
  char    *c;

  ret = NULL;
  if (node->space && !node->plus)
    c = " ";
  else
    c = "+";
  if (t[0] != '-')
    ret = ft_strjoin(c, t);
  return (ret);
}

void	flag_ord1(t_pf *node, char **t, int opt)
{
  char	*tmp;

  if (node->field)
    if ((tmp = field_width(*t, node)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
  if (node->precision)
    if ((tmp = precision(*t, node, opt)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
  if (node->diez || opt == PT)
    if ((tmp = diez(*t, opt)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
}

void	flag_ord2(t_pf *node, char **t, int opt)
{
  char	*tmp;

  tmp = NULL;
  if (node->precision)
    if ((tmp = precision(*t, node, opt)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
  if (node->diez || opt == PT)
    if ((tmp = diez(*t, opt)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
  if (node->field)
    if ((tmp = field_width(*t, node)))
      {
	ft_strdel(t);
	*t = tmp;
	tmp = NULL;
      }
}

char    *flag(t_pf *node, char **t, int opt)
{
  char    *tmp;

  tmp = NULL;
  if (node->zero && (!node->moins || !node->field))
    {
      flag_ord1(node, t, opt);
    }
  else
    {
      flag_ord2(node, t, opt);
    }
  if ((node->plus || node->space) \
      && (opt == S_INT || opt == PT))
    {
      if ((tmp = spaceplus(*t, node)))
	{
	  ft_strdel(t);
	  *t = tmp;
	  tmp = NULL;
	}
    }
  return (*t);
}

