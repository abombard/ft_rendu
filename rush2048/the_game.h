#ifndef THE_GAME_H
# define THE_GAME_H

# include <ncurses/curses.h>
# include <ncurses.h>
# include "libft.h"

typedef struct	s_swin
{
  int	x;
  int	y;
  int	oldx;
  int	oldy;
  int	done;
}		t_swin;

# define CARX(v) (v->x / 4)
# define CARY(v) (v->y / 4)

#endif
