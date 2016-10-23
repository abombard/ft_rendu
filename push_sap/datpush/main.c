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

t_int		*init_struc(int nb)
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
		(void)opt;
		if (check_errors(av) == -1)
			return (0);
		while (av[++x])
		{
			if (!av[x][0])
				continue ;
			n = ft_atoi(av[x]);
			if (!(tmp->next = init_struc(n)))
				return (0);
			tmp = tmp->next;
		}
		if (beg.next)
		  {
		    push_swap(&beg.next, ac);
		    del_struct(&beg.next);
		  }
	}
	ft_putchar('\n');
	return (0);
}
