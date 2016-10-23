/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 16:56:25 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 16:56:34 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void    swap(t_int **list)
{
	t_int   *tmp;

	tmp = *list;
	if (tmp && tmp->next)
    {
		ft_swap(&tmp->nb, &tmp->next->nb);
    }
}

void    sa(t_int **a)
{
	ft_putstr("sa ");
	swap(a);
}

void    sb(t_int **b)
{
	ft_putstr("sb ");
	swap(b);
}

void    ss(t_int **a, t_int **b)
{
	ft_putstr("ss ");
	swap(a);
	swap(b);
}
