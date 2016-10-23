/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:30:01 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 14:56:38 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void		function(t_int **a, t_int **b, int *tab, int opt)
{
	while (!inc(a) || !dec(b))
    {
		if (opt)
			print(a, b);
		if ((*a)->next && (*b)->next   \
			&& (*a)->nb > (*a)->next->nb \
			&& (*a)->nb != tab[1] && (*a)->next->nb != tab[1]	\
			&& (*b)->nb < (*b)->next->nb						\
			&& (*b)->nb != tab[0] && (*b)->next->nb != tab[0])
			ss(a, b);
		else if ((*a)->next && \
				 (*a)->nb > (*a)->next->nb							\
				 && (*a)->nb != tab[1] && (*a)->next->nb != tab[1])
		  sa(a, b);
		else if ((*b)->next && \
				 (*b)->nb < (*b)->next->nb							\
				 && (*b)->nb != tab[0] && (*b)->next->nb != tab[0])
		  sb(a, b);
		if (!inc(a) && !dec(b))
			rr(a, b);
		else if (!inc(a))
		  ra(a, b);
		else if (!dec(b))
		  rb(a, b);
    }
}

int		old_fun(t_int **a, t_int **b, int opt)
{
	int		i;
	int		pvt;
	t_int	*tmp;
	int	len = list_len(a);

	pvt = pivot(a, len);
	i = 0;
	if (inc(a))
	  return (0);
	while (i < len)
	  {
		if (inc(a) && !b)
		  return (0);
		tmp = *a;
		if (tmp->nb <= pvt)
			pb(a, b);
		else
		  ra(a, b);
		if (opt)
			print(a, b);
		i++;
	  }
	len = 0;
	len = curse(a, b, len, opt);
	while (*b)
		pa(a, b);
	return (len);
}
