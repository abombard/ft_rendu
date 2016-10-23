#ifndef LISP_H
# define LISP_H

# include <stdlib.h>
# include <unistd.h>

#define LISP 42

typedef int type;

typedef union
{
  struct 
  {
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
  }	bytes;
  char	c;
  char	*s;
  int	n;
  float	f;
  struct s_lisp	*lisp;
}	value;

typedef struct s_lisp
{
  type	type;
  value	content;
  struct s_lisp *next;
  struct s_lisp	*prev;
}              t_lisp;

t_lisp	*lspnew(value value, type type);
t_lisp	*lspdelone(t_lisp **beg, t_lisp **node);
void	lspdel(t_lisp **beg);
void	lspadd(t_lisp **beg, t_lisp *new);
void	lsppush(t_lisp **beg, t_lisp *new);
void	aff_node(t_lisp *node);
void	aff_lisp(t_lisp *beg);
int	lisp_len(t_lisp *beg);
t_lisp	*first(t_lisp *tmp);
t_lisp	*last(t_lisp *tmp);
t_lisp	*next(t_lisp *tmp);
t_lisp	*prev(t_lisp *tmp);
void	del_first(t_lisp **elem);
int	lspcmp_content(t_lisp *tmp, value v);
int	lspcmp(t_lisp *n1, t_lisp *n2);
t_lisp	*find_prev(t_lisp *tmp, value v);
t_lisp	*find_next(t_lisp *tmp, value v);
t_lisp	*lspcpy(t_lisp *src);
t_lisp	*find_elem(t_lisp *tmp, value v);

# endif
