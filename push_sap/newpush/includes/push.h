/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:06:42 by abombard          #+#    #+#             */
/*   Updated: 2015/02/17 14:57:22 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_H
# define PUSH_H

# include "my_printf.h"
# include "get_next_line.h"

typedef struct	s_int
{
  int		nb;
  struct s_int	*next;
}		t_int;

typedef struct	s_tab
{
  int	n;
  char	*(*f)(t_int **a, t_int **b);
}		t_tab;

int	curse(t_int **a, t_int **b, int count, int opt);
int	pivot(t_int **list, int len);
int	old_fun(t_int **a, t_int **b, int opt);
void	del_struct(t_int **list);
int		*vals(t_int **list);
int		inc(t_int **list);
int		dec(t_int **list);
int		list_len(t_int **list);
void		small_2(t_int **list, char c);
void		small_3a(t_int **list);
void		small_3b(t_int **list);
int			inc(t_int **list);
void		print(t_int **a, t_int **b);
void		fun(t_int **a, t_int **b);
void		push_swap(t_int **a, int ac);
int			check_errors(char **av);
int		push(t_int **a, t_int **b);
char		*pa(t_int **a, t_int **b);
char		*pb(t_int **a, t_int **b);
int		rotate(t_int **list);
char		*ra(t_int **a, t_int **b);
char		*rb(t_int **a, t_int **b);
char		*rr(t_int **a, t_int **b);
int		rev_rotate(t_int **list);
char		*rra(t_int **a, t_int **b);
char		*rrb(t_int **a, t_int **b);
char		*rrr(t_int **a, t_int **b);
int		swap(t_int **list);
char		*sa(t_int **a, t_int **b);
char		*sb(t_int **a, t_int **b);
char		*ss(t_int **a, t_int **b);

#endif
