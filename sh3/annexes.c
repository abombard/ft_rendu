/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:13:35 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 14:52:20 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		betw_char(char *pt, int len, char p)
{
	int	x;
	int	trig;

	x = 0;
	trig = 0;
	while (pt[x])
	{
		if (x > len)
			return (1);
		else if (x == len && trig == 0)
			return (0);
		else if (pt[x] == p && trig == 0)
			trig = 1;
		else if (pt[x] == p && trig == 1)
			trig = 0;
		x++;
	}
	return (1);
}

void	trim_tab(char ***tab)
{
	char	**t;
	char	*tmp;
	int		x;

	t = *tab;
	x = 0;
	while (t[x])
	{
		tmp = NULL;
		if ((tmp = ft_strtrim(t[x])))
		{
			ft_strdel(&t[x]);
			t[x] = tmp;
		}
		x++;
	}
}

void	access_error(char *path)
{
	if (access(path, F_OK) == -1)
		ft_putstr_fd("File does not exist: ", 2);
	if (access(path, X_OK | R_OK | W_OK) == -1)
		ft_putstr_fd("Permission denied: ", 2);
	ft_putendl_fd(path, 2);
}
