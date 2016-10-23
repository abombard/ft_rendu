#ifndef TCAPS_H
# define TCAPS_H

# include <curses.h>
# include <termcap.h>
# include <termios.h>

typedef struct  s_stock
{
  int     col;
  int     line;
  int     maxline;
  int     maxcol;
  int     lcol;
  int     lline;
  int     maxlen;
  int     fd;
  int     g_ret;
  char    *term;
  char    *home;
  char    *right;
  char    *left;
  char    *up;
  char    *down;
  char	*ts;
  char    *clr;
  char    *del;
  char	  *cd;
  char    *dl;
  char	  *del_line;
  char    *cr;
  char    *ret;
  char    *push;
  char    *pop;
  char    *set_ul;
  char    *unset_ul;
  char	*beg;
}               t_stock;

int	puti(int c);
int	init_termcaps(t_stock *info);

#endif
