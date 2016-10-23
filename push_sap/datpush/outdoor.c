/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdoor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 16:54:50 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 16:55:21 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

int		check_double(char **av)
{
	int   x;
	int   y;
	int   sv;

	sv = 0;
	x = 0;
	while (av[++x])
    {
		if (!av[x][0])
			continue ;
		sv = ft_atoi(av[x]);
		y = x;
		while (av[++y])
			if (ft_atoi(av[y]) == sv)
			{
				ft_putendl_fd("Error: same number appears twice", 2);
				return (-1);
			}
    }
	return (0);
}

int		check_errors(char **av)
{
	int             x;
	int             y;

	x = -1;
	while (av[++x])
    {
		y = -1;
		while (av[x][++y])
			if (ft_isdigit(av[x][y]))
				break ;
		if (!ft_isdigit(av[x][y]))
		{
			ft_strclr(av[x]);
			continue ;
		}
		if (ft_atol(av[x]) > 2147483647 || ft_atol(av[x]) < -2147483648)
		{
			ft_putendl_fd("1 of the arguments isnt an integer", 2);
			return (-1);
		}
    }
	if (check_double(av) == -1)
		return (-1);;
	return (0);
}
