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

int	rev_rotate(t_int **list)
{
	t_int   *tmp;
	t_int   *prev;

	if (!list || !*list)
	  return (0);
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
	return (1);
}

char    *rra(t_int **a, t_int **b)
{
  (void)b;
  if (!rev_rotate(a))
    return (NULL);
  return ("rra ");
}

char    *rrb(t_int **a, t_int **b)
{
  (void)a;
  if (!rev_rotate(b))
    return (NULL);
  return ("rrb ");
}

char    *rrr(t_int **a, t_int **b)
{
  if (!rev_rotate(a) || !rev_rotate(b))
    return (NULL);
  return ("rrr ");
}
