/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 16:56:07 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 16:56:17 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void    rotate(t_int **list)
{
	t_int   *tmp;

	if (list && *list && (*list)->next)
    {
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *list;
		(*list) = (*list)->next;
		tmp->next->next = NULL;
    }
}

void    ra(t_int **a)
{
	ft_putstr("ra ");
	rotate(a);
}

void    rb(t_int **b)
{
	ft_putstr("rb ");
	rotate(b);
}

void    rr(t_int **a, t_int **b)
{
	ft_putstr("rr ");
	rotate(a);
	rotate(b);
}
