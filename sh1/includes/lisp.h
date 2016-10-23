/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lisp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 15:35:03 by abombard          #+#    #+#             */
/*   Updated: 2015/05/11 15:51:55 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISP_H
# define LISP_H

# include <stdlib.h>
# include <unistd.h>
# include "tcaps.h"

# define LISP 42
# define OBJ 41

typedef int			t_type;

typedef union		u_value
{
	int				n;
	char			c;
	char			*s;
	float			f;
	struct s_lisp	*lisp;
}					t_value;

typedef struct		s_lisp
{
	char			*key;
	int				i;
	t_type			type;
	t_value			content;
	struct s_lisp	*next;
	struct s_lisp	*prev;
}					t_lisp;

t_lisp				*lspnew(t_value value, t_type type, char *key);
t_lisp				*lspdelone(t_lisp **beg, t_lisp **node);
void				lspdel(t_lisp **beg);
t_lisp				*lspadd(t_lisp **beg, t_lisp *new);
t_lisp				*lsppush(t_lisp **beg, t_lisp *new);
void				aff_node(t_lisp *node);
void				aff_lisp(t_lisp *beg);
int					lisp_len(t_lisp *beg);
int					lsplen_for(t_lisp *beg);
int					lsplen_back(t_lisp *beg);
t_lisp				*first(t_lisp *tmp);
t_lisp				*last(t_lisp *tmp);
t_lisp				*next(t_lisp *tmp);
t_lisp				*prev(t_lisp *tmp);
void				del_first(t_lisp **elem);
int					lspcmp_content(t_lisp *tmp, t_value v);
int					lspcmp(t_lisp *n1, t_lisp *n2);
t_lisp				*find_prev(t_lisp *tmp, t_value v);
t_lisp				*find_next(t_lisp *tmp, t_value v);
t_lisp				*lspcpy(t_lisp *src);
t_lisp				*find_elem(t_lisp *tmp, t_value v);
t_lisp				*search_by_key(t_lisp *tmp, char *key);
t_lisp				*extract_elem(t_lisp **elem);
t_lisp				*insert_elem(t_lisp **dst, t_lisp *src);
t_lisp				*extract_by_key(t_lisp *tmp, char *key);
t_lisp				*order_index(t_lisp *tmp);
t_lisp				*order_index_from(t_lisp *tmp);
void				clear_keys(t_lisp *tmp);

#endif
