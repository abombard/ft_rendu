/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 01:29:46 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:15:35 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	col(char *str, char c)
{
	int		x;
	int		counter;
	int		save;

	x = 0;
	save = 0;
	while (str[x])
	{
		counter = 0;
		while (str[x] != c && str[x])
		{
			counter = counter + 1;
			x = x + 1;
		}
		if (counter > save)
			save = counter;
		x = x + 1;
	}
	return (save == 0 ? 0 : save + 1);
}

static int	line(char *str, char c)
{
	int		x;
	int		counter;

	x = 0;
	counter = 0;
	while (str[x])
	{
		if (str[x] == c)
		{
			counter = counter + 1;
			while (str[x] == c && str[x])
				x = x + 1;
		}
		x = x + 1;
	}
	return (counter == 0 ? 0 : counter + 2);
}

static char	**build_tab(int nbline, int nbcol)
{
	char	**tab;
	int		x;

	x = 0;
	if (!nbline || !nbcol)
		return (NULL);
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

char		**ft_strsplit(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		x;

	if (s && c && (tab = build_tab(line((char*)s, c), col((char*)s, c))))
	{
		x = 0;
		i = 0;
		while (s[x])
		{
			j = 0;
			if (s[x] != c && s[x])
			{
				while (s[x] != c && s[x])
					tab[i][j++] = s[x++];
				tab[i++][j] = '\0';
			}
			while (s[x] == c && s[x])
				x++;
		}
		tab[i] = '\0';
	}
	return (tab);
}
