/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 14:48:58 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 16:54:33 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push.h"

void	print(t_int **a, t_int **b)
{
	t_int	*tmp;

	ft_putendl("____________________________");
	tmp = *a;
	ft_putendl("list a :");
	while (tmp)
    {
		ft_putnbr(tmp->nb);
		ft_putendl("");
		tmp = tmp->next;
    }
	tmp = *b;
	ft_putendl("");
	ft_putendl("list b :");
	while (tmp)
    {
		ft_putnbr(tmp->nb);
		ft_putendl("");
		tmp = tmp->next;
    }
	ft_putendl("");
}

void	ia(t_int **a, t_int **b)
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

void	push_swap(t_int **a, int opt)
{
	t_int	*b;

	b = NULL;

	int	*tab;
	t_int	*tmp;
	t_push	push;

	tmp = *a;
	push.opt = opt;
	push.len = 0;
	if (!(tab = malloc(sizeof(int) * 2)))
	  return ;
	tab[0] = 2147483647;
	tab[1] = -2147483648;
	while (tmp)
	  {
	    if (tmp->nb < tab[0])
	      tab[0] = tmp->nb;
	    if (tmp->nb > tab[1])
	      tab[1] = tmp->nb;
	    push.len += 1;
	    tmp = tmp->next;
	  }
	push.tab = tab;
	if (push.len == 2)
	  small_2(a, 'a');
	else if (push.len == 3)
	  small_3a(a);
	//    	ia(a, &b);
	else if (push.len > 1)
	  fun(a, &b, &push);
	print(a, &b);
	free(tab);
}

void		del_struct(t_int **list)
{
	t_int	*l;
	t_int *tmp;

	l = *list;
	while (l)
    {
		tmp = l->next;
		free(l);
		l = tmp;
    }
}

t_int		*init_struct(int nb)
{
	t_int	*ret;

	ret = NULL;
	if (!(ret = malloc(sizeof(t_int))))
		return (NULL);
	ret->nb = nb;
	ret->next = NULL;
	return (ret);
}

int	check_opt(char **av)
{
	if (ft_strcmp(av[1], "-v") == 0)
		return (1);
	return (0);
}

int		main(int ac, char **av)
{
	t_int	beg;
	t_int	*tmp;
	int		x;
	int		n;
	int		opt;

	if (ac > 1)
	{
		x = 0;
		tmp = &beg;
		tmp->next = NULL;
		opt = check_opt(av);
		if (check_errors(av) == -1)
			return (0);
		while (av[++x])
		{
			if (!av[x][0])
				continue ;
			n = ft_atoi(av[x]);
			if (!(tmp->next = init_struct(n)))
				return (0);
			tmp = tmp->next;
		}
		if (beg.next)
		  {
		    push_swap(&beg.next, opt);
		    del_struct(&beg.next);
		  }
	}
	ft_putchar('\n');
	return (0);
}
