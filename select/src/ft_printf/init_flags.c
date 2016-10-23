/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 20:01:34 by abombard          #+#    #+#             */
/*   Updated: 2015/02/05 16:41:07 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

int check_char(char **s, char c, int opt)
{
    char    *tmp;
    int     x;

    tmp = *s;
    x = 0;
    while (tmp[x])
    {
		if (c == 'l' && (tmp[x] == 'D' || tmp[x] == 'O' || tmp[x] == 'U' \
				|| tmp[x] == 'C' || tmp[x] == 'S'))
		{
			tmp[x] = ft_tolower(tmp[x]);
			return (1);
		}
        if (tmp[x] == c && (tmp[x + 1] != c || !opt))
        {
            tmp[x] = ' ';
            return (1);
        }
        x++;
    }
    return (0);
}

int check_doublechar(char **s, char c)
{
    char    *tmp;
    int     x;

    tmp = *s;
    x = 0;
    while (tmp[x])
    {
        if (tmp[x] == c && tmp[x + 1] == c)
        {
            tmp[x] = ' ';
            tmp[x + 1] = ' ';
            return (1);
        }
        x++;
    }
    return (0);
}

int check_field(char **s)
{
    char    *tmp;
    int     ret;
    int     x;

    tmp = *s;
    x = 0;
    while (tmp[x])
    {
        if (ft_isdigit(tmp[x]) && tmp[x] != '0' && tmp[x - 1] != '.')
        {
            ret = ft_atoi(&tmp[x]);
            while (tmp[x] && ft_isdigit(tmp[x]))
                tmp[x++] = ' ';
            return (ret);
        }
        x++;
    }
    return (0);
}

int     check_precision(char **s)
{
    char    *tmp;
    int     ret;
    int     x;

    tmp = *s;
    x = 0;
    while (tmp[x])
    {
        if (tmp[x] == '.')
        {
	  tmp[x++] = ' ';
	  while (tmp[x] && (tmp[x] == '.' || tmp[x] == '0'))
	    tmp[x++] = ' ';
	  if (!tmp[x] || !ft_isdigit(tmp[x]))
	    return (0);
	  ret = ft_atoi(&tmp[x]);
	  while (tmp[x] && ft_isdigit(tmp[x]))
	    tmp[x++] = ' ';
	  return (ret);
        }
        x++;
    }
    return (0);
}

void    init_flags(t_pf **list)
{
    t_pf    *tmp;
    char    *t;

    tmp = *list;
    while (tmp)
    {
		if (tmp->arg)
		{
			tmp->space = check_char(&tmp->arg, ' ', 0);
			tmp->precision = check_precision(&tmp->arg);
			tmp->field = check_field(&tmp->arg);
			tmp->zero = check_char(&tmp->arg, '0', 0);
			tmp->diez = check_char(&tmp->arg, '#', 0);
			tmp->plus = check_char(&tmp->arg, '+', 0);
			tmp->moins = check_char(&tmp->arg, '-', 0);
			tmp->hh = check_doublechar(&tmp->arg, 'h');
			tmp->h = check_char(&tmp->arg, 'h', 1);
			tmp->ll = check_doublechar(&tmp->arg, 'l');
			tmp->l = check_char(&tmp->arg, 'l', 1);
			tmp->j = check_char(&tmp->arg, 'j', 0);
			tmp->z = check_char(&tmp->arg, 'z', 0);
			t = ft_strtrim(tmp->arg);
			ft_strdel(&tmp->arg);
			tmp->arg = t;
			init_opt(&tmp);
		}
        tmp = tmp->next;
    }
}
