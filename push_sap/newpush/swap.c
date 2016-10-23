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
int    swap(t_int **list)
{
	t_int   *tmp;

	if (!list || !*list)
	  return (0);
	tmp = *list;
	if (tmp && tmp->next)
    {
		ft_swap(&tmp->nb, &tmp->next->nb);
    }
	return (1);
}

char    *sa(t_int **a, t_int **b)
{
  (void)b;
  if (!swap(a))
    return (NULL);
  return ("sa ");
}

char    *sb(t_int **a, t_int **b)
{
  (void)a;
  if (!swap(b))
    return (NULL);
  return ("sb ");
}

char    *ss(t_int **a, t_int **b)
{
  if (!swap(a))
    return (NULL);
  if (!swap(b))
    return (NULL);
  return ("ss ");
}
