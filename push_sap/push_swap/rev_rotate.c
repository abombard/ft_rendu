/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 16:55:37 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 16:55:56 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void	rev_rotate(t_int **list)
{
	t_int   *tmp;
	t_int   *prev;

	if (list && *list && (*list)->next)
    {
		prev = *list;
		while (prev->next->next)
			prev = prev->next;
		tmp = prev->next;
		tmp->next = *list;
		*list = tmp;
		prev->next = NULL;
    }
}

void    rra(t_int **a)
{
	ft_putstr("rra ");
	rev_rotate(a);
}

void    rrb(t_int **b)
{
	ft_putstr("rrb ");
	rev_rotate(b);
}

void    rrr(t_int **a, t_int **b)
{
	ft_putstr("rrr ");
	rev_rotate(a);
	rev_rotate(b);
}
