/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 17:36:58 by abombard          #+#    #+#             */
/*   Updated: 2014/12/29 17:37:31 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		col(char *str)
{
	int	x;
	int	counter;
	int	save;

	x = 0;
	save = 0;
	while (str[x])
	{
		counter = 0;
		while (str[x] && ft_isspace(str[x]) == 1)
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

int		line(char *str)
{
	int	x;
	int	counter;

	x = 0;
	counter = 0;
	while (str[x])
	{
		if (ft_isspace(str[x]) == 0)
			counter = counter + 1;
		while (str[x] && ft_isspace(str[x]) == 0)
			x = x + 1;
		x = x + 1;
	}
	return (counter + 2);
}

char	**build_tab(int nbline, int nbcol)
{
	char	**tab;
	char	*tab2;
	int		x;

	x = 0;
	tab = (char**)malloc(sizeof(char*) * nbline);
	if (tab == NULL)
		return (NULL);
	tab2 = (char*)malloc(sizeof(char) * (nbline * nbcol));
	if (tab2 == NULL)
		return (NULL);
	while (x < nbline)
	{
		tab[x] = &tab2[x * nbcol];
		x = x + 1;
	}
	return (tab);
}

char	**my_split_whitespace(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		x;

	x = 0;
	i = 0;
	tab = build_tab(line(str), col(str));
	while (str[x])
	{
		j = 0;
		while (str[x] && ft_isspace(str[x]) == 1)
		{
			tab[i][j] = str[x];
			x = x + 1;
			j = j + 1;
		}
		tab[i][j] = '\0';
		while (str[x] && ft_isspace(str[x]) == 0)
			x = x + 1;
		i = i + 1;
	}
	tab[i] = 0;
	return (tab);
}
