#include "push.h"

int	maj(t_int *list)
{
  int	sv;
  int	cmp;

  cmp = list->nb;
  sv = list->nb;
  while (list)
    {
      if (list->nb > sv)
	sv = list->nb;
      list = list->next;
    }
  return (cmp == sv);
}

void	getinfo(t_int **list, int *ret)
{
  t_int	*tmp;
  int	x;

  x = 0;
  tmp = *list;
  while (tmp)
    {
      ret[x] = tmp->nb;
      tmp = tmp->next;
    }
}

int	curs(t_int **a, t_int **b, int ac)
{
  int	count;
  int	x;
  int	tab[ac];

  x = 0;
  count = 1;
  pb(a, b);
  ft_printf("%s, %s, %s, %s\n", BEG, BLUE, "beginning curs", END);
  while (1)
    {
      print(a, b);
      if (inc(a) && (!*b || dec(b)))
	break ;
      if ((*a)->nb > (*b)->nb)
	{
	  pa(a, b);
	  getinfo(a, b, tab);
	  tab[0]
	  sb(a, b);
	  pa(a, b);
      else
	pa(a, b);
      rra(a, b);
      x += 1;
      count += 2;
    }
  while (*b)
      pa(a, b);
  count += 1;
  return (count);
}

void	push_swap(t_int **a, int ac)
{
  t_int *b;
  int	count;

  b = NULL;
  count = 0;
  ft_printf("starting..\n");
  ac--;
  if (inc(a))
    break ;
  count = curs(a, &b, ac);
  print(a, &b);
  ft_printf("count = %d\n", count);
}
