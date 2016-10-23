#include "push.h"

int	largest(t_int **a, t_int **b)
{
  t_int *tmp;
  int	ret;
  int	*lim = vals(a);

  (void)b;
  ret = 0;
  tmp = *a;
  while (tmp->next)
  {
    if (tmp->nb == lim[1] && tmp->next->nb == lim[0])
      ret += 2;
    tmp = tmp->next;
  }
  return (ret);
}

int	factor(t_int **a, t_int **b)
{
  t_int *tmp;
  int	ret;
  int	dif;
  int	*lim = vals(a);

  (void)b;
  ret = 0;
  tmp = *a;
  int sv = tmp->nb;
  while (tmp->next)
    {
      dif = tmp->next->nb - tmp->nb;
      if (dif > 0 && ret < dif && dif != lim[0] - lim[1])
	ret = dif;
      tmp = tmp->next;
    }
  dif = sv - tmp->nb;
  if (dif > 0 && ret < dif)
    ret = dif;
  ret -= largest(a, b);
  return (ret);
}

t_int *save_list(t_int **list)
{
  t_int	beg;
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

int	re_init(t_int **a, t_int **b, t_int **sva, t_int **svb)
{
  del_struct(a);
  del_struct(b);
  *a = save_list(sva);
  *b = save_list(svb);
  return (1);
}

int	*test_swap(t_int **a, t_int **b, t_int **sva, t_int **svb)
{
  int	c1, c2, next;
  int	*ret;

  c1 = ss(a, b) ? factor(a, b) : -1;
  re_init(a, b, sva, svb);
  c2 = sa(a, b) ? factor(a, b) : -1;
  next = c1 < c2 ? 1 : 2;
  c1 = c1 < c2 ? c1 : c2;
  re_init(a, b, sva, svb);
  c2 = sb(a, b) ? factor(a, b) : -1;
  c1 = c1 < c2 ? c1 : c2;
  next = c1 < c2 ? next : 3;
  re_init(a, b, sva, svb);
  if (!(ret = malloc(sizeof(int) * 2)))
    return (NULL);
  ret[0] = next;
  ret[1] = c1;
  return (ret);
}

int	*test_rotate(t_int **a, t_int **b, t_int **sva, t_int **svb)
{
  int	c1, c2, next;
  int	*ret;

  c1 = rr(a, b) ? factor(a, b) : -1;
  re_init(a, b, sva, svb);
  c2 = ra(a, b) ? factor(a, b) : -1;
  next = c1 < c2 ? 4 : 5;
  c1 = c1 < c2 ? c1 : c2;
  re_init(a, b, sva, svb);
  c2 = rb(a, b) ? factor(a, b) : -1;
  c1 = c1 < c2 ? c1 : c2;
  next = c1 < c2 ? next : 6;
  re_init(a, b, sva, svb);
  if (!(ret = malloc(sizeof(int) * 2)))
    return (NULL);
  ret[0] = next;
  ret[1] = c1;
  return (ret);
}

int	*test_rev_rotate(t_int **a, t_int **b, t_int **sva, t_int **svb)
{
  int	c1, c2, next;
  int	*ret;

  c1 = rrr(a, b) ? factor(a, b) : -1;
  re_init(a, b, sva, svb);
  c2 = rra(a, b) ? factor(a, b): -1;
  next = c1 < c2 ? 7 : 8;
  c1 = c1 < c2 ? c1 : c2;
  re_init(a, b, sva, svb);
  c2 = rrb(a, b) ? factor(a, b) : -1;
  c1 = c1 < c2 ? c1 : c2;
  next = c1 < c2 ? next : 9;
  re_init(a, b, sva, svb);
  if (!(ret = malloc(sizeof(int) * 2)))
    return (NULL);
  ret[0] = next;
  ret[1] = c1;
  return (ret);
}

int	*test_push(t_int **a, t_int **b, t_int **sva, t_int **svb)
{
  int	c1, c2, next;
  int	*ret;

  c1 = pa(a, b) ? factor(a, b) : -1;
  re_init(a, b, sva, svb);
  c2 = pb(a, b) ? factor(a, b): -1;
  c1 = c1 < c2 ? c1 : c2;
  next = c1 < c2 ? 10 : 11;
  re_init(a, b, sva, svb);
  if (!(ret = malloc(sizeof(int) * 2)))
    return (NULL);
  ret[0] = next;
  ret[1] = c1;
  return (ret);
}

t_tab	*init()
{
  t_tab *ret;

  ret = malloc(sizeof(t_tab) * 11);
  if (!ret)
    return (NULL);
  ret[0].n = 1;
  ret[0].f = &ss;
  ret[1].n = 2;
  ret[1].f = &sa;
  ret[2].n = 3;
  ret[2].f = &sb;
  ret[3].n = 4;
  ret[3].f = &rr;
  ret[4].n = 5;
  ret[4].f = &ra;
  ret[5].n = 6;
  ret[5].f = &rb;
  ret[6].n = 7;
  ret[6].f = &rrr;
  ret[7].n = 8;
  ret[7].f = &rra;
  ret[8].n = 9;
  ret[8].f = &rrb;
  ret[9].n = 10;
  ret[9].f = &pa;
  ret[10].n = 11;
  ret[10].f = &pb;
  return (ret);
}

void	do_it(t_int **a, t_int **b, int *c, int opt)
{
  t_tab	*fun;
  int	x;

  (void)opt;
  x = 0;
  fun = init();
  while (x < 11)
    {
      if (c[0] == fun[x].n)
	ft_putstr(fun[x].f(a, b));
      x++;
    }
  free(fun);
}

int	curse(t_int **a, t_int **b, int count, int opt)
{
  t_int *sva = save_list(a);
  t_int *svb = save_list(b);
  int	*c1, *c2;

  int	*lim = vals(a);
  if ((*a)->nb == lim[0] && ((*a)->next->nb == lim[1]))
    {
      sa(a, b);
      return (curse(a, b, ++count, opt));
    }
  if (opt)
    print (a, b);
  if (count > 100)
    return (-1);
  if (inc(a))
    return (count);
  c1 = test_swap(a, b, &sva, &svb);
  c2 = test_rotate(a, b, &sva, &svb);
  c1 = c1[1] > c2[1] ? c1 : c2;
  c2 = test_rev_rotate(a, b, &sva, &svb);
  c1 = c1[1] > c2[1] ? c1 : c2;
  c2 = test_push(a, b, &sva, &svb);
  c1 = c1[1] > c2[1] ? c1 : c2;
  if (factor(a, b) > factor(&sva, &svb))
    do_it(a, b, c1, opt);
  else
    {
      sa(a, b);
      ra(a, b);
    }
  del_struct(&sva);
  del_struct(&svb);
  return (curse(a, b, ++count, opt));
}

void	push_swap(t_int **a, int opt)
{
  t_int *b;
  int	count;

  (void)opt;
  count = 0;
  b = NULL;
  //  if (list_len(a) < 7)
  count = curse(a, &b, count, opt);
    //  else
  //count = old_fun(a, &b, opt);
  ft_putendl("");
  ft_putstr("count total : ");
  ft_putnbr(count);
  ft_putendl("");
}
