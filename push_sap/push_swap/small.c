#include "push.h"

void	small_2(t_int **a, char c)
{
  if (c == 'a' ? !inc(a) : !dec(a))
    c == 'a' ? sa(a) : sb(a);
}

int *vals(t_int **list)
{
  t_int *tmp;
  int	*tab;

  tmp = *list;
  tab = malloc(sizeof(int) * 2);
  if (!tab)
    return (NULL);
  tab[0] = 2147483647;
  tab[1] = -2147483648;
  while (tmp)
    {
      if (tmp->nb < tab[0])
	tab[0] = tmp->nb;
      if (tmp->nb > tab[1])
	tab[1] = tmp->nb;
      tmp = tmp->next;
    }
  return (tab);
}

void	small_3a(t_int **a)
{
  t_int *tmp;
  t_int *last;
  int	*t;

  ft_putstr(" || ");
  t = vals(a);
  while (!inc(a))
    {
      last = *a;
      while (last->next)
	last = last->next;
      tmp = *a;
      if (tmp->nb == t[1] || tmp->nb == t[0])
	ra(a);
      else if (tmp->nb > tmp->next->nb)
	sa(a);
      else if (last->nb == t[0])
	rra(a);
    }
  ft_putstr(" || ");
  free(t);
}

void	small_3b(t_int **b)
{
  t_int *tmp;
  t_int *last;
  int	*t;

  ft_putstr(" || ");
  t = vals(b);
  while (!dec(b))
    {
      last = *b;
      while (last->next)
	last = last->next;
      tmp = *b;
      if (tmp->nb == t[1] || tmp->nb == t[0])
	rb(b);
      else if (tmp->nb < tmp->next->nb)
	sb(b);
      else if (last->nb == t[1])
	rrb(b);
  ft_putstr(" || ");
    }
  free(t);
}

int	list_len(t_int **list)
{
  t_int *tmp;
  int	x;

  x = 0;
  if (!list || !*list)
    return (0);
  tmp = *list;
  while (tmp->next)
    {
      x += 1;
      tmp = tmp->next;
    }
  return (x);
}

int	*list_to_tab(t_int *list)
{
  int	*tab;
  int	len;
  int	x;

  len = list_len(&list);
  tab = malloc(sizeof(int) * (len + 1));
  tab[0] = len;
  x = 1;
  while (x <= len)
    {
      tab[x++] = list->nb;
      list = list->next;
    }
  return (tab);
}

void	small(t_int **a, t_int **b, t_push *push)
{
  (void)a; (void)b; (void)push;
  t_int *last;
  int *t;

  t = vals(a);

  while (!inc(a) || *b)
    {
      last = *a;
      while (last->next)
	last = last->next;
      if ((*a)->nb == t[1])
	ra(a);
      else if (last->nb == t[0])
	rra(a);
      else if ((*a)->nb > (*a)->next->nb)
	sa(a);
      else if (last->nb == t[0])
	rra(a);
      else
	ra(a);
    }
}
