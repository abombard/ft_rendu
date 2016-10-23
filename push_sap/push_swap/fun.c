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

int			dec(t_int **list)
{
	t_int	*tmp;

	if (!list || !*list)
		return (1);
	tmp = *list;
	while (tmp->next)
    {
		if (tmp->nb > tmp->next->nb)
			tmp = tmp->next;
		else
			return (0);
    }	
	return (1);
}

int			inc(t_int **list)
{
	t_int *tmp;

	if (!list || !*list)
		return (1);
	tmp = *list;
	while (tmp->next)
    {
		if (tmp->nb < tmp->next->nb)
			tmp = tmp->next;
		else
			return (0);
    }
	return (1);
}


t_int *save_list(t_int **list)
{
  t_int beg;
  t_int *sv;
  t_int *tmp;

  if (!list || !*list)
    return (NULL);
  tmp = *list;
  sv = &beg;
  while (tmp)
    {
      if ((sv->next = malloc(sizeof(t_int))))
        {
          sv = sv->next;
          sv->nb = tmp->nb;
        }
      tmp = tmp->next;
    }
  sv->next = NULL;
  return (beg.next);
}

int		function(t_int **a, t_int **b, int *tab, int opt, int count)
{
	if (!inc(a) && !dec(b))
	  return (count);
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
			sa(a);
		else if ((*b)->next && \
				 (*b)->nb < (*b)->next->nb							\
				 && (*b)->nb != tab[0] && (*b)->next->nb != tab[0])
			sb(b);
		count += 1;
		t_int *sva = save_list(a);
		t_int *svb = save_list(b);
		if (!inc(a) && !dec(b))
		  {
		    rr(a, b);
		    rrr(&sva, &svb);
		    if ((function(a, b, tab, opt, count)) < (function(&sva, &svb, tab, opt, count)))
			return (function(a, b, tab, opt, ++count));
		    else
		      return (function(&sva, &svb, tab, opt, ++count));
		  }
		else if (!inc(a))
		  {
			ra(a);
			rra(&sva);
			if (function(a, b, tab, opt, count) < function(&sva, &svb, tab, opt, count))
			  return (function(a, b, tab, opt, ++count));
			else
			  return (function(&sva, &svb, tab, opt, ++count));
		  }
		else if (!dec(b))
		  {
			rb(b);
			rrb(&svb);
			if (function(a, b, tab, opt, count) < function(&sva, &svb, tab, opt, count))
			  return (function(a, b, tab, opt, ++count));
			else
			  return (function(&sva, &svb, tab, opt, ++count));
		  }
		return (count);
}

int			pivot(t_int **list, t_push *push)
{
	t_int 	*tmp;
	t_int	*beg;
	int		sv;
	int		count;

	beg = *list;
	while (beg)
    {
		sv = beg->nb;
		tmp = *list;
		count = 0;
		while (tmp)
		{
			if (tmp->nb <= sv)
				count += 1;
			tmp = tmp->next;
		}
		if (count >= push->len / 2 && count <= push->len / 2)
			return (sv);
		beg = beg->next;
    }
	return (0);
}

void		fun(t_int **a, t_int **b, t_push *push)
{
  int	count = 0;
	int		i;
	int		pvt;
	t_int	*tmp;

	pvt = pivot(a, push);
	i = 0;
	if (inc(a))
		return ;
	while (i < push->len)
	  {
		if (inc(a) && !b)
			return ;
		tmp = *a;
		if (tmp->nb <= pvt)
			pb(a, b);
		else
			ra(a);
		if (push->opt)
			print(a, b);
		i++, count++;
	  }
	int ret = function(a, b, push->tab, push->opt, count);
	ft_putstr("count = "); ft_putnbr(ret); ft_putendl("");
	while (*b)
		pa(a, b);
	print(a, b);
}
