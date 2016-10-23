#ifndef SELECT_H
# define SELECT_H

#include "my_printf.h"
#include "libft.h"
#include "colors.h"
#include <termcap.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>

typedef struct	s_lisp
{
  char		*content;
  int		rang;
  int		select;
  int		on;
  struct s_lisp	*next;
  struct s_lisp *last;
}		t_lisp;

typedef struct	s_stock
{
  int	col;
  int	line;
  int	maxline;
  int	maxcol;
  int	lcol;
  int	lline;
  int	maxlen;
  int	fd;
  int	g_ret;
  char	*term;
  char	*home;
  char	*clr;
  char	*del;
  char	*ret;
  char	*push;
  char	*pop;
  char	*set_ul;
  char	*unset_ul;
}		t_stock;

# define HOME tputs(info->home, info->fd, &puti)
# define CLR tputs(info->clr, info->fd, &puti)
# define DEL tputs(tgoto(info->del, info->col, info->maxlen), info->fd, &puti)
# define RET tputs(tgoto(info->ret, info->col, info->line), info->fd, &puti)
# define PUSH tputs(info->push, info->fd, &puti);
# define POP tputs(info->pop, info->fd, &puti);
# define BOLD_GREEN { tputs(BOLD, info->fd, &puti); tputs(GREEN, info->fd, &puti); }
# define END_COL tputs(END, info->fd, &puti)
# define NXTLINE act(info, 3, tmp)
# define PREVLINE act(info, 2, tmp)
# define BOLD_BLUE { tputs(BOLD, info->fd, &puti); tputs(BLUE, info->fd, &puti); }
# define SET_UL tputs(info->set_ul, info->fd, &puti);
# define UNSET_UL tputs(info->unset_ul, info->fd, &puti);

int		print_list(t_lisp *tmp, t_stock *info);
char	*cursor(int opt);
int		ftw(t_lisp **beg, int maxlen, struct termios ter, struct termios oldter);
int	puti(int c);

#endif
