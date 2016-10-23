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

int    push(t_int **a, t_int **b)
{
	t_int   *tmpb;

	if (!b || !*b)
	  return (0);
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
	return (1);
}

char    *pa(t_int **a, t_int **b)
{
  if (!push(a, b))
    return (NULL);
  return ("pa ");
}

char    *pb(t_int **a, t_int **b)
{
  if (!push(b, a))
    return (NULL);
  return ("pb ");
}
