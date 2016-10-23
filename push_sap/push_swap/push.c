/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:22:16 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 14:02:12 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void    push(t_int **a, t_int **b)
{
	t_int   *tmpb;

	if (b && *b)
    {
		tmpb = *b;
		if ((*b)->next)
			*b = (*b)->next;
		else
			*b = NULL;
		tmpb->next = *a;
		*a = tmpb;
    }
}

void    pa(t_int **a, t_int **b)
{
	ft_putstr("pa ");
	push(a, b);
}

void    pb(t_int **a, t_int **b)
{
	ft_putstr("pb ");
	push(b, a);
}
