#include "lisp.h"
#include "my_printf.h"
#include "libft.h"

t_lisp *lspnew(value value, type type)
{
  t_lisp *new;

  if ((type == STRING && !value.s) || (type == LISP && value.lisp == NULL)) 
    return (NULL);
  new = malloc(sizeof(t_lisp));
  if (!new)
    return (NULL);
  new->type = type;
  new->content = value;
  new->prev = NULL;
  new->next = NULL;
  return (new);
}

t_lisp	*lspdelone(t_lisp **beg, t_lisp **node)
{
  t_lisp *ret;

  ret = NULL;
  if (*node)
    {
      if ((*node)->prev)
	{
	  ret = (*node)->prev;
	  ret->next = (*node)->next;
	  if ((*node)->next)
	    (*node)->next->prev = ret;
	}
      else if ((*node)->next)
	{
	  ret = (*node)->next;
	  *beg = ret;
	}
      else
	*beg = NULL;
      if ((*node)->type == STRING)
	free(&(*node)->content.s);
      else if ((*node)->type == LISP)
      	lspdel(&(*node)->content.lisp);
      free(*node);
      *node = NULL;
    }
  return (ret);
}

void	lspdel(t_lisp **beg)
{
  t_lisp *tmp;

  while (*beg)
    {
      tmp = (*beg)->next;
      if ((*beg)->type == STRING && (*beg)->content.s != NULL)
	ft_strdel(&(*beg)->content.s);
      free(*beg);
      *beg = NULL;
      *beg = tmp;
    }
}

void	lspadd(t_lisp **beg, t_lisp *new)
{
  if (new)
    {
      if (!*beg)
	{
	  *beg = new;
	}
      else
	{
	  new->next = *beg;
	  *beg = new;
	}
    }
}

void	lsppush(t_lisp **beg, t_lisp *new)
{
  t_lisp *tmp;

  if (new)
    {
      if (!*beg)
	{
	  *beg = new;
	}
      else
	{
	  tmp = *beg;
	  while (tmp->next)
	    tmp = tmp->next;
	  tmp->next = new;
	  new->prev = tmp;
	}
    }
}

void	aff_node(t_lisp *node)
{
  if (node->type == CHAR)
    ft_printf("%c", node->content.c);
  else if (node->type == STRING)
    ft_printf("%s\n", node->content.s);
  else if (node->type == S_INT)
    ft_printf("%d\n", node->content.n);
  else if (node->type == LISP)
    aff_lisp(node->content.lisp);
}

void	aff_lisp(t_lisp *beg)
{
  //  int	ret;

  //  ret = 0;
  if (!beg)
    ft_printf("(Null)");
  while (beg)
    {
      aff_node(beg);
      beg = beg->next;
    }
  //  if (ret)
  //  ft_printf("\n");
}

int	lisp_len(t_lisp *beg)
{
  int ret;

  beg = first(beg);
  ret = 0;
  while (beg)
    {
      ret++;
      beg = beg->next;
    }
  return (ret);
}

t_lisp	*first(t_lisp *tmp)
{
  while (tmp && tmp->prev)
    tmp = tmp->prev;
  return (tmp);
}

t_lisp	*last(t_lisp *tmp)
{
  while (tmp && tmp->next)
    tmp = tmp->next;
  return (tmp);
}

t_lisp	*next(t_lisp *tmp)
{
  return (tmp && tmp->next ? tmp->next : tmp);
}

t_lisp	*prev(t_lisp *tmp)
{
  return (tmp && tmp->prev ? tmp->prev : tmp);
}

void	del_first(t_lisp **elem)
{
  t_lisp	*tmp;

  if (!(tmp = *elem))
    return ;
  if (!tmp->prev)
    *elem = (*elem)->next;
  else
    tmp = first(*elem);
  if (tmp->type == STRING)
    ft_strdel(&tmp->content.s);
  free(tmp);
  ft_printf("Echo\n");
  aff_lisp(first(*elem));
}

t_lisp	*lspcpy(t_lisp *src)
{
  t_lisp	*dst;
  t_lisp	*tmp;

  dst = NULL;
  while (src)
    {
      tmp = lspnew(src->content, src->type);
      if (!tmp)
	return (NULL);
      lsppush(&dst, tmp);
      src = src->next;
    }
  return (dst);
}

int	lspcmp(t_lisp *n1, t_lisp *n2)
{
  if (n1 && n2 && n1->type == n2->type)
    {
      if ((n1->type == CHAR && n1->content.c == n2->content.c) ||
	  (n1->type == STRING && ft_strcmp(n1->content.s, n2->content.s) == 0) ||
	  (n1->type == S_INT && n1->content.n == n2->content.n))
	return (1);
      else if (n1->type == LISP)
	{
	  t_lisp *tmp1 = n1->content.lisp;
	  t_lisp *tmp2 = n2->content.lisp;
	  while (tmp1 && tmp2)
	    {
	      if (!lspcmp(tmp1, tmp2))
		return (0);
	      tmp1 = tmp1->next;
	      tmp2 = tmp2->next;
	    }
	  return (1);
	}
    }
  return (0);
}

int	lspcmp_content(t_lisp *tmp, value v)
{
  if ((tmp->type == CHAR && v.c == tmp->content.c) ||
      (tmp->type == STRING && ft_strcmp(v.s, tmp->content.s) == 0) ||
      (tmp->type == S_INT && v.n == tmp->content.n))
      return (1);
  else if (tmp->type == LISP)
    return (lspcmp(tmp->content.lisp, v.lisp));
  return (0);
}

t_lisp	*find_elem(t_lisp *node, value v)
{
  node = first(node);
  return (find_next(node, v));
}

t_lisp	*find_prev(t_lisp *tmp, value v)
{
  while (tmp)
    {
      if (lspcmp_content(tmp, v))
	break ;
      tmp = tmp->prev;
    }
  return (tmp);
}

t_lisp	*find_next(t_lisp *tmp, value v)
{
  while (tmp)
    {
      if (lspcmp_content(tmp, v))
	break ;
      tmp = tmp->next;
    }
  return (tmp);
}

