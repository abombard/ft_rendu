/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lisp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 15:58:46 by abombard          #+#    #+#             */
/*   Updated: 2015/05/11 17:59:35 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lisp.h"
#include "my_printf.h"
#include "libft.h"

t_lisp	*lspnew(t_value value, t_type type, char *key)
{
	t_lisp	*new;

	if ((type == STRING && !value.s) || (type == LISP && value.lisp == NULL))
		return (NULL);
	new = malloc(sizeof(t_lisp));
	if (!new)
		return (NULL);
	new->type = type;
	new->key = key ? ft_strdup(key) : NULL;
	new->content = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	lspdel_elem(t_lisp **node)
{
	if ((*node)->type == STRING)
		free(&(*node)->content.s);
	else if ((*node)->type == LISP)
		lspdel(&(*node)->content.lisp);
	if ((*node)->key)
		ft_strdel(&(*node)->key);
	free(*node);
	*node = NULL;
}

t_lisp	*lspdelone(t_lisp **beg, t_lisp **node)
{
  t_lisp	*ret;

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
	  (*node)->next->prev = ret;
	  ret->prev = NULL;
	  *beg = ret;
	}
      else
	*beg = NULL;
      lspdel_elem(node);
    }
  return (ret);
}



/*
t_lisp	*lspdelone(t_lisp **node)
{
	t_lisp	*ret;

	ret = NULL;
	if (*node)
	{
	  if ((*node)->prev || (*node)->next)
	    ret = (*node)->prev ? (*node)->prev : (*node)->next;
	  if ((*node)->next && (*node)->prev)
	    {
	      ret->next = (*node)->next;
	      ret->next->prev = (*node)->prev;
	    }
	  lspdel_elem(node);
	}
	return (ret);
	}*/

void	lspdel(t_lisp **beg)
{
	t_lisp	*tmp;

	*beg = first(*beg);
	while (*beg)
	{
		tmp = (*beg)->next;
		if ((*beg)->type == STRING && (*beg)->content.s != NULL)
			ft_strdel(&(*beg)->content.s);
		else if ((*beg)->type == LISP)
			lspdel(&(*beg)->content.lisp);
		if ((*beg)->key)
			ft_strdel(&(*beg)->key);
		free(*beg);
		*beg = NULL;
		*beg = tmp;
	}
}

t_lisp	*lspadd(t_lisp **beg, t_lisp *new)
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
	return (*beg);
}

t_lisp	*lsppush(t_lisp **beg, t_lisp *new)
{
	t_lisp	*tmp;

	if (new)
	{
		if (!*beg)
		{
			*beg = new;
			new->i = 0;
		}
		else
		{
			tmp = *beg;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->i = tmp->i + 1;
		}
	}
	return (new);
}

void	aff_node(t_lisp *node)
{
  if (!node)
    return ;
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
	if (!beg)
		ft_printf("(Null)");
	while (beg)
	{
		aff_node(beg);
		beg = beg->next;
	}
}

int		lisp_len(t_lisp *beg)
{
	int	ret;

	beg = first(beg);
	ret = 0;
	while (beg)
	{
		ret++;
		beg = beg->next;
	}
	return (ret);
}

int		lsplen_for(t_lisp *beg)
{
	int ret;

	ret = 0;
	while (beg)
	{
		ret++;
		beg = beg->next;
	}
	return (ret);
}

int		lsplen_back(t_lisp *beg)
{
	int ret;

	ret = 0;
	while (beg)
	{
		ret++;
		beg = beg->prev;
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

	if (!(*elem))
		return ;
	if (!(*elem)->prev)
		*elem = (*elem)->next;
	tmp = first(*elem);
	if (tmp)
	  {
	    if (tmp->type == STRING)
	      ft_strdel(&tmp->content.s);
	    if (tmp->key)
	      ft_strdel(&tmp->key);
	    if (tmp->next)
	      tmp->next->prev = NULL;
	    free(tmp);
	  }
}

t_lisp	*lspcpy(t_lisp *src)
{
	t_lisp	*dst;
	t_lisp	*tmp;

	dst = NULL;
	while (src)
	{
		tmp = lspnew(src->content, src->type, src->key);
		if (!tmp)
			return (NULL);
		lsppush(&dst, tmp);
		src = src->next;
	}
	return (dst);
}

int		lspcmp(t_lisp *n1, t_lisp *n2)
{
	t_lisp *tmp1;
	t_lisp *tmp2;

	if (n1 && n2 && n1->type == n2->type)
	{
		if ((n1->type == CHAR && n1->content.c == n2->content.c) ||
			(n1->type == STRING && ft_strcmp(n1->content.s, n2->content.s) == 0)
			|| (n1->type == S_INT && n1->content.n == n2->content.n))
			return (1);
		else if (n1->type == LISP)
		{
			tmp1 = n1->content.lisp;
			tmp2 = n2->content.lisp;
			while (tmp1 && tmp2)
			{
				if (!lspcmp(tmp1, tmp2))
					return (0);
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
			return (!tmp1 && !tmp2 ? 1 : 2);
		}
	}
	return (0);
}

int		lspcmp_content(t_lisp *tmp, t_value v)
{
	if ((tmp->type == CHAR && v.c == tmp->content.c) ||
		(tmp->type == STRING && ft_strcmp(v.s, tmp->content.s) == 0) ||
		(tmp->type == S_INT && v.n == tmp->content.n))
		return (1);
	else if (tmp->type == LISP)
		return (lspcmp(tmp->content.lisp, v.lisp));
	return (0);
}

t_lisp	*find_elem(t_lisp *node, t_value v)
{
	node = first(node);
	return (find_next(node, v));
}

t_lisp	*find_prev(t_lisp *tmp, t_value v)
{
	while (tmp)
	{
		if (lspcmp_content(tmp, v))
			break ;
		tmp = tmp->prev;
	}
	return (tmp);
}

t_lisp	*find_next(t_lisp *tmp, t_value v)
{
	while (tmp)
	{
		if (lspcmp_content(tmp, v))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_lisp	*insert_elem(t_lisp **dst, t_lisp *src)
{
  t_lisp	*end;

	if (src)
	{
	  if (!*dst)
	    {
	      *dst = src;
	      order_index(*dst);
	    }
	  else
	    {
	      end = src;
	      end->i = (*dst)->next ? (*dst)->next->i : (*dst)->i + 1;
	      while (end->next)
		{
		  end = end->next;
		  end->i = end->prev->i + 1;
		}
	      end->next = (*dst)->next;
	      order_index_from(end);
	      if ((*dst)->next)
		(*dst)->next->prev = end;
	      (*dst)->next = src;
	      src->prev = *dst;
	    }
	}
	return (src);
}

t_lisp	*search_by_key(t_lisp *node, char *key)
{
	t_lisp	*ret;
	t_lisp	*tmp;
	int		x;

	x = 0;
	ret = NULL;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			if ((tmp = lspnew(node->content, node->type, node->key)))
			{
				tmp->i = x++;
				lsppush(&ret, tmp);
			}
		node = node->next;
	}
	return (ret);
}

t_lisp	*extract_elem(t_lisp **elem)
{
	t_lisp	*tmp;

	if ((tmp = *elem))
	{
		if (tmp->prev && tmp->next)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		else
		{
			if (tmp->prev)
				tmp->prev->next = NULL;
			if (tmp->next)
				tmp->next->prev = NULL;
		}
	}
	return (tmp);
}

t_lisp	*extract_by_key(t_lisp *node, char *key)
{
	t_lisp	*ret;
	t_lisp	*tmp;
	int		x;

	x = 0;
	ret = NULL;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			if ((tmp = extract_elem(&node)))
			{
				tmp->i = x++;
				lsppush(&ret, tmp);
				continue ;
			}
		node = node->next;
	}
	return (ret);
}

t_lisp	*order_index(t_lisp *tmp)
{
  int		x;
  t_lisp	*beg;

  x = 0;
  beg = first(tmp);
  tmp = beg;
  while (tmp)
    {
      tmp->i = x++;
      tmp = tmp->next;
    }
  return (beg);
}

t_lisp	*order_index_from(t_lisp *tmp)
{
  t_lisp	*beg;

  beg = tmp;
  tmp = tmp->next;
  beg->i = beg->prev ? beg->prev->i + 1 : 0;
  while (tmp)
    {
      tmp->i = tmp->prev->i + 1;
      tmp = tmp->next;
    }
  return (beg);  
}

void	clear_keys(t_lisp *tmp)
{
  while (tmp)
    {
      ft_strdel(&tmp->key);
      tmp = tmp->next;
    }
}
