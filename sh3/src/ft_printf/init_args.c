/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:10:32 by abombard          #+#    #+#             */
/*   Updated: 2015/02/04 19:14:46 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

t_pf    *init_struct(void)
{
	t_pf  *ret;

	ret = NULL;
	if (!(ret = (t_pf*)malloc(sizeof(t_pf))))
		return (NULL);
	ret->string = NULL;
	ret->arg = NULL;
	ret->next = NULL;
	ret->opt = 0;
	return (ret);
}

int		is_arg(char c)
{
	if (c == ' ' || c == '0' || c == '#' || c == '+' || c == '-' \
		|| c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == '.'
	    || ft_isdigit(c))
		return (1);
	return (0);
}

char    *get_string(char *s)
{
    char    *ret;
    int     x;

    x = 0;
	ret = NULL;
    while (s[x] && s[x] != '%')
        x++;
    if (x == 0)
      return (NULL);
    if (!(ret = ft_strsub(s, 0, x)))
        return (NULL);
    return (ret);
}

char    *get_arg(char *s)
{
    char    *ret;
    int     x;

	ret = NULL;
	x = 0;
	while (s[x] && (is_arg(s[x])))
        x++;
    if (!s[x])
		return (NULL);
    if (!(ret = ft_strsub(s, 0, x + 1)))
        return (NULL);
    return (ret);
}

t_pf    *init_args(char *fmt)
{
    t_pf    beg;
    t_pf    *tmp;
    int     x;
	int		len;

	len = ft_strlen(fmt);
    tmp = &beg;
    x = 0;
    while (x < len)
    {
        if (!(tmp->next = init_struct()))
		{
			del_pf(&beg.next);
            return (NULL);
		}
        tmp = tmp->next;
        if ((tmp->string = get_string(&fmt[x])))
            x += ft_strlen(tmp->string);
		if (fmt[x] == '%')
			x++;
        if ((tmp->arg = get_arg(&fmt[x])))
			x += ft_strlen(tmp->arg);
    }
    return (beg.next);
}
