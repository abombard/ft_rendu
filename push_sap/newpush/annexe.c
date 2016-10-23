#include "push.h"

int                     dec(t_int **list)
{
  t_int   *tmp;

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

int                     inc(t_int **list)
{
  t_int *tmp;

  if (!list || !*list)
    return (0);
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

int *vals(t_int **list)
{
  t_int *tmp;
  int   *tab;

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

int                     pivot(t_int **list, int len)
{
  t_int   *tmp;
  t_int   *beg;
  int             sv;
  int             count;

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
      if (count >= len / 2 && count <= len / 2)
	return (sv);
      beg = beg->next;
    }
  return (0);
}

int     *list_to_tab(t_int *list)
{
  int   *tab;
  int   len;
  int   x;

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

int     list_len(t_int **list)
{
  t_int *tmp;
  int   x;

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

