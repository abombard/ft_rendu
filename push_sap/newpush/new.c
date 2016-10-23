#include "push.h"

int	test(t_int **a, t_int **b, int count, char *(*f)(t_int **a, t_int **b))
{
  t_int *sva = save_list(a);
  t_int *svb = save_list(b);

  f(sva, svb);
  curse(&sva, &svb, 
}

int	curse(t_int **a, t_int **b, int opt, int count)
{

  if (ss(a, b) && curse(a, b, opt, count) < curse(&sva, &svb, opt, count))
    {
      if (sa(a, b) && 
    }
}

void	push_swap(t_int **a, int opt)
{
  t_int *b;
  int	count;

  count = 0;
  b = NULL;
  count = curse(a, &b, opt, ++count);
  ft_putendl("");
  ft_putstr("count: ");
  ft_putnbr(count); 
  ft_putendl("");
}
