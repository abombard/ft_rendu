/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:09:07 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:10:25 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int			stop(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static void	linencol(char *s, int *line, int *col)
{
	int	x;
	int	c;

	*line = 2;
	*col = 0;
	c = 0;
	x = 0;
	while (s[x])
	{
		if (stop(s[x]) && !betw_char(s, x, '"'))
		{
			if (s[x - 1] != s[x])
			{
				*line += 2;
				if (c > *col)
					*col = c;
			}
			c = -1;
		}
		x++, c++;
	}
	if (c > *col)
		*col = c;
	*col += 1;
}

static char	**build_tab(char *cmd)
{
	char	**tab;
	int		nbline;
	int		nbcol;
	int		x;

	nbline = 0;
	nbcol = 0;
	linencol(cmd, &nbline, &nbcol);
	if (nbline == 2 || nbcol == 1)
		return (NULL);
	x = 0;
	tab = (char**)malloc(sizeof(char*) * nbline);
	if (tab == NULL)
		return (NULL);
	while (x < nbline)
	{
		if (!(tab[x] = (char*)malloc(sizeof(char) * nbcol)))
			return (NULL);
		x += 1;
	}
	return (tab);
}

char		**split_redirections(char *cmd)
{
	char	**tab;
	char	*pt;
	int		x;
	int		y;
	int		i;

	if (!(tab = build_tab(cmd)))
		return (NULL);
	pt = cmd;
	x = 0;
	i = 0;
	while (pt[i])
	{
		y = 0;
		if (!stop(pt[i]) || betw_char(cmd, i, '"'))
			while (pt[i] && (!stop(pt[i]) || betw_char(cmd, i, '"')))
				tab[x][y++] = pt[i++];
		else
			while (pt[i] && stop(pt[i]))
				tab[x][y++] = pt[i++];
		tab[x][y] = 0;
		x++, i++;
	}
	tab[x] = NULL;
	trim_tab(&tab);
	return (tab);
}
