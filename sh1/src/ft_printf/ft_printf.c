/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 19:23:36 by abombard          #+#    #+#             */
/*   Updated: 2015/02/05 17:46:20 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

char	*foo(t_pf *node, va_list ap)
{
	t_pfun	*f;
	char	*s;
	int		x;

	s = NULL;
	if (!(f = init_fun()))
		return (NULL);
	x = 0;
	while (x < 8)
	{
		if (node->opt == f[x].opt)
		{
			if (!(s = f[x].fun(ap, node)))
				return (NULL);
			if (!(s = flag(node, &s, node->opt)))
				return (NULL);
		}
		x++;
	}
	free(f);
	return (s);
}

int	init_printf(t_pf *tmp, va_list ap)
{
	char	*t;
	int	x;
	char	buf[PRINTF_BUFSIZE];

	x = 0;
	while (tmp)
	{
	  if (tmp->string)
	    {
	      ft_strcpy(&buf[x], tmp->string);
	      x += ft_strlen(tmp->string);
	    }
	  if ((t = foo(tmp, ap)))
	    {
	      ft_strcpy(&buf[x], t);
	      x += ft_strlen(t);
	      ft_strdel(&t);
	    }
	  del_pf(&tmp);
	}
	buf[x] = 0;
	ft_putstr(buf);
	return (x);
}

int		ft_printf(const char *fmt, ...)
{
  va_list	ap;
  t_pf		*list;
  int		ret;

  if (!fmt)
	  return (0);
  list = NULL;
  if (!(list = init_list((char *)fmt)))
	  return (0);
  va_start(ap, fmt);
  ret = init_printf(list, ap);
  ret = ret == 0 ? 1 : ret;
  va_end(ap);
  return (ret);
}
