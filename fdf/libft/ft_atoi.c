/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:53:41 by abombard          #+#    #+#             */
/*   Updated: 2014/11/21 09:17:02 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r')
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	long long	nbr;
	int			x;

	nbr = 0;
	x = 1;
	while (*str)
	{
		if ((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)) == 1)
			x = (*(str++) == '-' ? -1 : 1);
		if (ft_isdigit(*str) == 1)
		{
			while (ft_isdigit(*str) == 1)
			{
				nbr = (nbr * 10) + (*str - '0');
				str++;
			}
			return ((int)(nbr * x));
		}
		if (ft_isspace(*str) == 0)
			str++;
		else
			return (0);
	}
	return (0);
}
