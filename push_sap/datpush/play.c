#include "push.h"

void    ia(t_int **a, t_int **b)
{
  char *buf;

  print(a, b); ft_putendl("");
  buf = NULL;
  ft_putstr("> ");
  get_next_line(0, &buf);
  if (ft_strcmp(buf, "q") == 0)
    exit (1);
  else if (ft_strcmp(buf, "sa") == 0)
    swap(a);
  else if (ft_strcmp(buf, "sb") == 0)
    swap(b);
  else if (ft_strcmp(buf, "ss") == 0)
    {
      swap(a);
      swap(b);
    }
  else if (ft_strcmp(buf, "ra") == 0)
    rotate(a);
  else if (ft_strcmp(buf, "rb") == 0)
    rotate(b);
  else if (ft_strcmp(buf, "rr") == 0)
    {
      rotate(a);
      rotate(b);
    }
  else if (ft_strcmp(buf, "rra") == 0)
    rev_rotate(a);
  else if (ft_strcmp(buf, "rrb") == 0)
    rev_rotate(b);
  else if (ft_strcmp(buf, "rrr") == 0)
    {
      rev_rotate(a);
      rev_rotate(b);
    }
  else if (ft_strcmp(buf, "pb") == 0)
    push(b, a);
  else if (ft_strcmp(buf, "pa") == 0)
    push(a, b);
  else
    ft_putendl("Use: sa sb ss ra rb rr rra rrb rrr pa pb");
  ft_strdel(&buf);
  return (ia(a, b));
}
