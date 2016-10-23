/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitwhitespace_but.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:10:49 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:12:50 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int	col(char *str, char p)
{
	int	x;
	int	counter;
	int	save;

	x = 0;
	save = 0;
	while (str[x])
	{
		counter = 0;
		while (str[x] \
				&& (ft_isspace(str[x]) == 1 || betw_char(str, x, p) == 1))
		{
			counter = counter + 1;
			x = x + 1;
		}
		if (counter > save)
			save = counter;
		x = x + 1;
	}
	return (save + 1);
}

static int	line(char *str, char p)
{
	int	x;
	int	counter;

	x = 0;
	counter = 0;
	while (str[x])
	{
		if (ft_isspace(str[x]) && betw_char(str, x, p) == 0)
		{
			counter = counter + 1;
			while (str[x] && ft_isspace(str[x]))
				x = x + 1;
		}
		x = x + 1;
	}
	return (counter + 2);
}

static char	**build_tab(int nbline, int nbcol)
{
	char	**tab;
	int		x;

	x = 0;
	tab = (char**)malloc(sizeof(char*) * nbline);
	if (tab == NULL)
		return (NULL);
	while (x < nbline)
	{
		if (!(tab[x] = (char*)malloc(sizeof(char) * nbcol)))
			return (NULL);
		x = x + 1;
	}
	return (tab);
}

char		**my_split_whitespace_but(char *str, char p)
{
	char	**tab;
	int		i;
	int		j;
	int		x;

	x = 0;
	i = 0;
	if (!(tab = build_tab(line(str, p), col(str, p))))
		return (NULL);
	while (str[x])
	{
		j = 0;
		while (str[x] \
				&& (!ft_isspace(str[x]) || betw_char(str, x, p) == 1))
		{
			tab[i][j] = str[x];
			x++, j++;
		}
		tab[i][j] = '\0';
		while (str[x] && ft_isspace(str[x]))
			x += 1;
		i += 1;
	}
	tab[i] = 0;
	return (tab);
}
