/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:04:13 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:04:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		get_length(char **t)
{
	int	x;

	x = 0;
	while (t[x])
		x++;
	return (x);
}

char	**rebuild_tab(char ***t1, char ***t2, int trig)
{
	char	**new;
	int		len;
	int		x;
	int		y;

	if (!t1 || !t2 || !*t1 || !*t2)
		return (NULL);
	len = get_length(*t1) + get_length(*t2);
	if (!(new = (char **)malloc(sizeof(*new) * len)))
		return (NULL);
	x = 0;
	y = 0;
	len = 0;
	if (trig >= 0)
		ft_strdel(&(*t1)[trig]);
	else
		trig = get_length(*t1);
	while (x < trig)
		new[len++] = (*t1)[x++];
	while ((*t2)[y])
		new[len++] = (*t2)[y++];
	while ((*t1)[++trig])
		new[len++] = (*t1)[trig];
	free(*t1);
	return (new);
}
