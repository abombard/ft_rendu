/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 17:56:00 by abombard          #+#    #+#             */
/*   Updated: 2015/05/11 18:04:26 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

# define TEH_LEFT 1
# define TEH_RIGHT 2

int	get_line(t_stock *caps, t_lisp *tmp)
{
  int	x;
  int	cmp;
  int	cur;

  x = 0;
  if (tmp)
    {
      cur = len_back(tmp);
      cmp = cur == -1 ? caps->maxcol - 5 : caps->maxcol - 1;
      cur = cur == -1 ? lsplen_back(tmp) : cur;
      while ( 1 )
	{
	  if ((caps->maxcol) * x + cmp > cur)
	    return (x + 1);
	  x++;
	}
    }
  return (x);
}

int	len_back(t_lisp *tmp)
{
  int		len;

  if (!tmp)
    return (-1);
  len = 0;
  while (tmp->prev && tmp->i != -1)
    {
      len++;
      tmp = tmp->prev;
    }
  if (tmp->i == -1)
    return (len);
  return (-1);
}

int	len_check(t_lisp *tmp)
{
  int	len;

  len = 0;
  tmp = last(tmp);
  while (tmp->prev && tmp->i != -1)
    {
      len++;
      tmp = tmp->prev;
    }
  return (len);
}

int	another_line(t_stock *caps, t_lisp *tmp, int opt)
{
  int	x;
  int	len;
  int	cmp;
  int	cur;

  if (!tmp)
    return (0);
  cur = len_back(tmp);
  if (cur == -1)
    cmp = opt == TEH_LEFT ? caps->maxcol - 5 : caps->maxcol - 4;  
  else
    cmp = opt == TEH_LEFT ? caps->maxcol - 1 : caps->maxcol;
  cur = cur == -1 ? lsplen_back(tmp) - 1 : cur;
  x = 0;
  len = len_check(tmp);
  while (x * caps->maxcol < len)
    {
      if ((caps->maxcol) * x + cmp == cur)
	return (1);
      x++;
    }
  return (0);
}

void    key_left(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int	i;

  (void)hist;
  if (*tmp && !(*tmp)->key && (*tmp)->i > -1)
    {
      if (!(*tmp)->prev)
	(*tmp)->key = ft_strdup("42");
      *tmp = prev(*tmp);
      if (another_line(caps, *tmp, TEH_LEFT))
	{
	  tputs(caps->up, 2, &puti);
	  i = caps->maxcol;
	  while (i--)
	    tputs(caps->right, 1, &puti);
	}
      else
	tputs(caps->left, 1, &puti);
    }
}

void    key_right(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  (void)hist;
  if (*tmp && ((*tmp)->next || first(*tmp)->key))
    {
      if (!(*tmp)->prev && first(*tmp)->key)
	ft_strdel(&first(*tmp)->key);
      else
	*tmp = next(*tmp);
      if (another_line(caps, *tmp, TEH_RIGHT))
	{
	  tputs(caps->down, 2, &puti);
	  tputs(caps->cr, 1, &puti);
	}
      else
	tputs(caps->right, 1, &puti);
    }
}

void    key_down(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int len = get_line(caps, *tmp);

  if (*hist)
    {
      *tmp = first(*tmp);
      if ((*hist)->next)
        {
          *hist = next(*hist);
          lspdel(tmp);
          *tmp = last(lspcpy((*hist)->content.lisp));
        }
      else
        lspdel(tmp);
      while (len && --len)
	tputs(caps->up, 2, &puti);
      tputs(caps->cr, 1, &puti);
      tputs(caps->cd, 1, &puti);
      ft_printf("$> ");
      if (*tmp)
        aff_lisp(first(*tmp));
      *tmp = last(*tmp);
    }
}

void    key_up(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int len = get_line(caps, *tmp);

  if (*hist)
    {
      *tmp = first(*tmp);
      if (find_elem(*hist, (t_value)(*tmp)))
		  *hist = prev(*hist);
      lspdel(tmp);
      *tmp = last(lspcpy((*hist)->content.lisp));
      if (*tmp)
	  {
	    while (len && --len)
	      tputs(caps->up, 2, &puti);
	    tputs(caps->cr, 2, &puti);
	    tputs(caps->cd, 2, &puti);
	    ft_printf("$> ");
	    if (*tmp)
	      aff_lisp(first(*tmp));
	    *tmp = last(*tmp);
	  }
    }
}

int	allgood(t_lisp *tmp, char c1, char c2)
{
  int	trig;

  trig = 0;
  while (tmp)
    {
      if (tmp->content.c == c1)
	trig++;
      else if (tmp->content.c == c2)
	trig--;
      tmp = tmp->next;
    }
  return (trig ? 0 : 1);
}

void    key_enter(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  if (*tmp)
    {
      if (allgood(first(*tmp), '(', ')'))
	{
	  int l = get_line(caps, *tmp);
	  int ml = get_line(caps, last(*tmp));
	  if (lisp_len(*hist) > 10)
	    del_first(hist);
	  *tmp = first(*tmp);
	  clear_keys(*tmp);
	  order_index(*tmp);
	  //ft_printf("There u go l: %d, ml: %d\n", l, ml);
	  lsppush(hist, lspnew((t_value)(*tmp), LISP, NULL));
	  *hist = last(*hist);
	  while (l <= ml)
	    {
	      ft_printf("\n");
	      l++;
	    }
	  send_cmd(*tmp);
	  *tmp = NULL;
	}
      else
	{
	  *tmp = last(*tmp);
	  (*tmp)->i = -1;
	  return (ft_putstr("\n"));
	}
    }
  else
      ft_printf("\n");    
  ft_printf("$> ");
}

void    key_del(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  t_lisp *beg;

  (void)hist;
  if (*tmp && !(*tmp)->key)
    {
      if (!(*tmp)->prev)
	{
	  del_first(tmp);
	  if (*tmp)
	    (*tmp)->key = ft_strdup("42");
	}
      else
	{
	  beg = first(*tmp);
	  *tmp = lspdelone(&beg, tmp);
	}
      tputs(caps->left, 1, &puti);
      tputs(caps->del, 1, &puti);
    }
}
