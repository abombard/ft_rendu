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

# include "libft.h"
# include "get_next_line.h"

typedef struct	s_push
{
  int	opt;
  int	*tab;
  int	len;
}		t_push;

typedef struct	s_int
{
  int		nb;
  struct s_int	*next;
}		t_int;

t_int *save_list(t_int **list);
int		*vals(t_int **list);
int		inc(t_int **list);
int		dec(t_int **list);
int		list_len(t_int **list);
void		small_2(t_int **list, char c);
void		small_3a(t_int **list);
void		small_3b(t_int **list);
void		small(t_int **a, t_int **b, t_push *push);
int			inc(t_int **list);
void		print(t_int **a, t_int **b);
void		fun(t_int **a, t_int **b, t_push *push);
int			check_errors(char **av);
void		push(t_int **a, t_int **b);
void		pa(t_int **a, t_int **b);
void		pb(t_int **a, t_int **b);
void		rotate(t_int **list);
void		ra(t_int **a);
void		rb(t_int **b);
void		rr(t_int **a, t_int **b);
void		rev_rotate(t_int **list);
void		rra(t_int **a);
void		rrb(t_int **b);
void		rrr(t_int **a, t_int **b);
void		swap(t_int **list);
void		sa(t_int **a);
void		sb(t_int **b);
void		ss(t_int **a, t_int **b);

#endif
