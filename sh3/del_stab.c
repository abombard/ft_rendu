/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_stab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:13:53 by abombard          #+#    #+#             */
/*   Updated: 2015/02/04 15:13:56 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	del_stab(char ***tab)
{
	char	**t;
	int		x;

	x = 0;
	t = *tab;
	while (t[x])
		ft_strdel(&t[x++]);
	free(t);
}
