#include "push.h"

int	is_lowest(t_int *tmp, int cmp)
{
  while (tmp)
    {
      if (tmp->nb < cmp)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

int	is_highest(t_int *tmp, int cmp)
{
  while (tmp)
    {
      if (tmp->nb > cmp)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

int	where_is_lowest(t_int *list, int ac)
{
  t_int *tmp;
  int	x;
  int	index;
  int	low;

  x = 0;
  index = 0;
  low = 2147483647;
  tmp = list;
  while (tmp)
    {
      if (tmp->nb < low)
	{
	  index = x;
	  low = tmp->nb;
	}
      tmp = tmp->next;
      x++;
    }
  x = ac - index;
  return (x <= ac / 2 ? x : -x);
}

int	non_ordered_nodes(t_int *tmp)
{
  int	count;
  t_int	*beg;
  int	trig;

  trig = 0;
  beg = tmp;
  count = 0;
  while (tmp->next)
    {
      if (tmp->nb > tmp->next->nb)
	count += 1;
      if ((is_highest(beg, tmp->nb) || (is_lowest(beg, tmp->next->nb))))
	{
	  if (is_highest(beg, tmp->nb))
	    trig = 1;
	  if (is_lowest(beg, tmp->next->nb))
	    trig = trig == 1 ? 3 : 2;
	}
      tmp = tmp->next;
    }
  if (trig == 3 && count == 1)
    count = 0;
  if (tmp->nb > beg->nb && trig != 3)
    count += 1;
  return (count);
}

int	get_wrong_node(t_int *list, int ac)
{
  int	tab[ac];
  int	x;
  t_int	*tmp;

  x = 0;
  tmp = list;
  while (tmp)
    {
      tab[x++] = tmp->nb;
      tmp = tmp->next;
    }
  x = -1;
  while (++x < ac - 1)
    if (tab[x] > tab[x + 1])
      {
	ft_swap(&tab[x], &tab[x + 1]);
	x = -1;
      }
  tmp = list;
  while (tmp->next)
    {
      x = -1;
      while (++x < ac)
	if (tmp->nb == tab[x])
	  {
	    if (tmp->next->nb == tab[x + 1] || tmp->next->nb == tab[x + 2])
	      tmp = tmp->next;
	    else
	      return (tmp->next->nb);
	  }
      tmp = tmp->next;
    }
  return (0);
}

int	*non_ordered_node_wrong_pos(t_int *list, int ac)
{
  int	*node;

  node = malloc(sizeof(int) * 2);
  node[0] = 0;
  node[1] = get_wrong_node(list, ac);
  while (list->nb != node[1])
    {
      node[0] += 1;
      list = list->next;
    }
  return (node);
}

int	faster_way(int x, int ac)
{
  int	rev_x;
  int	ret;

  rev_x = ac - x;
  ret = rev_x < x ? -rev_x : x;
  return (ret);
}

int	good_place(t_int *tmp, int cmp)
{
  t_int *last;
  t_int *beg;

  beg = tmp;
  last = tmp;
  while (last->next)
    last = last->next;
  while (tmp)
    {
      if (tmp->nb == cmp)
	break ;
      tmp = tmp->next;
    }
  if (!tmp)
    {
      tmp = beg;
      if (((tmp->nb > cmp || is_lowest(beg, tmp->nb)) 
		&& (last->nb < cmp || is_highest(beg, last->nb)))
	     && !(is_lowest(beg, tmp->nb) && is_highest(beg, last->nb)))
	return (1);
    }
  else
    {
      tmp = beg;
      if (is_lowest(tmp, cmp))
	{
	  if (tmp->nb == cmp && is_highest(beg, last->nb))
	    return (1);
	  while (tmp->next->nb != cmp)
	    tmp = tmp->next;
	  if (is_highest(beg, tmp->nb))
	    return (1);
	}
      else if (is_highest(tmp, cmp))
	{
	  if (tmp->nb != cmp)
	    while (tmp->next->nb != cmp)
	      tmp = tmp->next;
	  if (is_lowest(beg, tmp->nb))
	    return (1);
	}
      else if (tmp->nb == cmp)
	{
	  if (tmp->next->nb > cmp && last->nb < cmp)
	    return (1);
	}
      else
	{
	  while (tmp->next->nb != cmp)
	    tmp = tmp->next;
	  if (tmp->nb < cmp && tmp->next->next->nb > cmp)
	    return(1);
	}
    }
  return (0);
}

int	non_ordered_node_good_pos(t_int *list, int cmp)
{
  t_int *tmp;
  int	index;

  index = 0;
  tmp = list;
  tmp = list;
  if (is_lowest(tmp, cmp))
    {
      while (!is_highest(list, tmp->nb))
	{
	  tmp = tmp->next;
	  index++;
	}
      index++;
    }
  else if (is_highest(tmp, cmp))
    {
      while (!is_lowest(list, tmp->nb))
	{
	  tmp = tmp->next;
	  index++;
	}
    }
  else
    {
      while (tmp->next && !(tmp->nb < cmp && cmp < tmp->next->nb))
	{
	  tmp = tmp->next;
	  index++;
	}
      index++;
    }
  return (index);
}

int	order_nodes(t_int **a, t_int **b, int ac)
{
  char	*(*f)(t_int **, t_int **);
  int	*node;
  int	x;
  int	y;
  int	dist;
  int	count;

  count = 0;
  node = non_ordered_node_wrong_pos(*a, ac);
  x = node[0];
  y = non_ordered_node_good_pos(*a, node[1]);
  if (ABS(faster_way(x, ac)) < ABS(faster_way(y, ac)))
    {
      dist = faster_way(x, ac);
      f = dist < 0 ? &rra : &ra;
      while ((*a)->nb != node[1])
	{
	  ft_putstr(f(a, b));
	  count++;
	  print(a, b);
	}
      dist = faster_way(y, ac);
      f = dist < 0 ? &rra : &ra;
      if (dist < 0)
	{
	  if (faster_way(x - y, ac) < 0)
	    ft_putstr(f(a, b));
	  else
	    ft_putstr(pb(a, b));
	  print(a, b);
	  count++;
	}
      while (!good_place(*a, node[1]))
	{
	  if (faster_way(x - y, ac) < 0)
	    {
	      ft_putstr(sa(a, b));
	      count++;
	      print(a, b);
	      if (good_place(*a, node[1]))
		break ;
	    }
	  ft_putstr(f(a, b));
	  count++;
	  print(a, b);
	}
      if (faster_way(x - y, ac) < 0)
	{
	  ft_putstr(pa(a, b));
	  count++;
	  print(a, b);
	}
    }
  else
    {
      dist = faster_way(y, ac);
      f = dist < -1 ? &rra : &ra;
      if (dist == -1)
	dist = 0;
      while (dist)
	{
	  ft_putstr(f(a, b));
	  print(a, b);
	  dist += dist < 0 ? 1 : -1;
	  count++;
	}
      while (!good_place(*a, node[1]))
	{
	  ft_putstr(pb(a, b));
	  count++;
	  print(a, b);
	  if (good_place(*a, node[1]))
	    break ;
	}
      ft_putstr(f(a, b));
      count++;
      print(a, b);
      while (*b)
	{
	  ft_putstr(pa(a, b));
	  print(a, b);
	  count++;
	}
    }
  free(node);
  return (count);
}

int	check_end(t_int *beg, int ac)
{
  int	cmp1;
  int	cmp2;
  int	i;
  t_int *tmp;

  cmp1 = 0;
  cmp2 = 0;
  i = 0;
  tmp = beg;
  while (tmp->next)
    {
      if (tmp->nb > tmp->next->nb && !(is_highest(beg, tmp->nb) && is_lowest(beg, tmp->next->nb)))
	{
	  if (i < ac / 2 - 0.6)
	    cmp1++;
	  else
	    cmp2++;
	}
      i++;
      tmp = tmp->next;
    }
  return (cmp1 < cmp2);
}

int	special_end(t_int **a, t_int **b, int count)
{
  t_int *last;

  last = *a;
  while (last->next)
    last = last->next;
  if ((*a)->nb < last->nb && !is_highest(*a, last->nb))
    {
      ft_putstr(rra(a, b));
      print(a, b);
      if (count)
	{
	  ft_putstr(sa(a, b));
	  print(a, b);
	  count++;
	}
      return special_end(a, b, count + 1);
    }
  return (count);
}

int	parser(t_int **a, t_int **b, int ac)
{
  int	count;
  int	trig = 0;

  count = 0;
  while (!inc(a))
    {
      if (check_end(*a, ac) && !trig)
	{
	  count += special_end(a, b, 0);
	  trig++;
	}
      else if (non_ordered_nodes(*a) == 1)
	{
	  count += order_nodes(a, b, ac);
	}
      else
	{
	  if (is_lowest(*a, (*a)->nb))
	    {
	      ft_putstr(pb(a, b));
	      ac--;
	    }
	  else if ((*a)->nb > (*a)->next->nb 
		   && !(is_highest(*a, (*a)->nb) && is_lowest(*a, (*a)->next->nb)))
	    ft_putstr(sa(a, b));
	  else if (where_is_lowest(*a, ac) < 0)
	    ft_putstr(ra(a, b));
	  else
	    ft_putstr(rra(a, b));
	  print(a, b);
	  count += 1;
	}
    }
  return (count);
}

int	rebuild_pile(t_int **a, t_int **b)
{
  int	count;

  count = 0;
  while (*b)
    {
      ft_putstr(pa(a, b));
      count += 1;
      print(a, b);
    }
  return (count);
}

void	push_swap(t_int **a, int ac)
{
  t_int *b;
  t_int *tmp;
  int	count;
  int	len;

  (void)ac;
  tmp = *a;
  len = 0;
  while (tmp)
    {
      tmp = tmp->next;
      len++;
    }
  count = 0;
  b = NULL;
  ft_printf("Original list:\n");
  print(a, &b);
  count += parser(a, &b, len + 1);
  count += rebuild_pile(a, &b);
  ft_printf("count = %d\n", count);
}
