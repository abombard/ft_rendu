/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_but.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:13:08 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:14:22 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int	col(char *str, char c, char p)
{
	int	x;
	int	counter;
	int	save;

	x = 0;
	save = 0;
	counter = 0;
	while (str[x])
	{
	  if (str[x] == c && !betw_char(str, x, p))
	    {
	      if (counter > save)
		save = counter;
	      counter = 0;
	    }
	  counter++, x++;
	}
	return (save + 1);
}

static int	line(char *str, char c, char p)
{
	int	x;
	int	counter;

	x = 0;
	counter = 0;
	if (str[x++] != p)
	  counter += 1;
	while (str[x])
	{
	  if (str[x] == c && str[x - 1] != c && betw_char(str, x, p) == 0)
	    counter = counter + 1;
	  x = x + 1;
	}
	if (str[x - 1] != c)
	  counter += 1;
	return (counter);
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
	  if (!(tab[x] = (char*)ft_memalloc(nbcol + 1)))
			return (NULL);
		x = x + 1;
	}
	tab[x] = NULL;
	return (tab);
}

char		**ft_strsplit_but(const char *s, char c, char p)
{
	char	**tab;
	int		i;
	int		j;
	int		x;

	tab = NULL;
	if (s && c && (tab = build_tab(line((char*)s, c, p), col((char*)s, c, p))))
	{
		x = 0;
		i = 0;
		while (s[x])
		{
			j = 0;
			while (s[x]					\
			       && (s[x] != c || betw_char((char*)s, x, p)))
			  tab[i][j++] = s[x++];
			j ? i++ : x++;
		}
		tab[i] = 0;
	}
	return (tab);
}
