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

int    rotate(t_int **list)
{
	t_int   *tmp;

	if (!list || !*list)
	  return (0);
	if (list && *list && (*list)->next)
    {
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *list;
		(*list) = (*list)->next;
		tmp->next->next = NULL;
    }
	return (1);
}

char    *ra(t_int **a, t_int **b)
{
  (void)b;
  if (!rotate(a))
    return (NULL);
  return ("ra ");
}

char    *rb(t_int **a, t_int **b)
{
  (void)a;
  if (!rotate(b))
    return (NULL);
  return ("rb ");
}

char    *rr(t_int **a, t_int **b)
{
  if (!rotate(a) || !rotate(b))
      return (NULL);
  return ("rr ");
}
