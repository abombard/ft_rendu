#include "the_game.h"

void	free_num(int ***numb)
{
  int	**num;

  num = *numb;
  free(num[0]);
  free(num);
}

int	**init_num()
{
  int	**num;
  int	*num2;
  int	x;

  x = 0;
  if (!(num = malloc(sizeof(int*) * 4)))
    return (NULL);
  if (!(num2 = malloc(sizeof(int) * 4 * 4)))
    return (NULL);
  while (x < 4)
    {
      num[x] = &num2[x * 4];
      x++;
    }
  return (num);
}

void	*init_curse()
{
  void	*win;

  if (!(win = initscr()))
    return (NULL);
  raw();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  return (win);
}

void	set_init(int **num)
{
  int	x;
  int	y;

  x = 0;
  while (x < 4)
    {
      y = 0;
      while (y < 4)
	{
	  num[x][y] = 0;
	  y++;
	}
      x++;
    }
}

void	print_tab(void *win, t_swin *sw)
{
  int	x;
  float	h;
  float	v;

  h = CARY(sw);
  v = CARX(sw);
  x = 1;
  while (x < 4)
    {
      move(h * x, 0);
      hline('-', sw->x);
      x++;
    }
  x = 1;
  while (x < 4)
    {
      move(0, v * x);
      vline('|', sw->y);
      x++;
    }
  box(win, '|', '~');
}

void	malloc_error()
{
  ft_putendl_fd("malloc error", 2);
  exit(0);
}

void	print_num(void *win, int **num, t_swin *sw)
{
  int	x;
  int	y;
  char	*tmp;

  tmp = NULL;
  x = 0;
  while (x < 4)
    {
      y = 0;
      while (y < 4)
	{
    	  if (num[x][y] != 0)
	    {
	      if (!(tmp = ft_itoa(num[x][y])))
		malloc_error();
	      mvwprintw((WINDOW*)win, CARY(sw) / 2 + (x * CARY(sw))
			, CARX(sw) / 2 + (y * CARX(sw)), tmp);
	      ft_strdel(&tmp);
	    }
	  y++;
	}
      x++;
    }
}

void	draw(void *win, t_swin *sw, int **num)
{
  clear();
  refresh();
  print_tab(win, sw);
  print_num(win, num, sw);
}

void	init_game(void *win, int ***num, t_swin *sw)
{
  int	n;
  int	x;
  int	y;

  sw->done = 0;
  set_init(*num);
  n = rand() % 2 == 0 ? 2 : 4;
  x = rand() % 4;
  y = rand() % 4;
  (*num)[x][y] = n;
  n = rand() % 2 == 0 ? 2 : 4;  
  while ((*num)[x][y] != 0)
    {
      x = rand() % 4;
      y = rand() % 4;
    }
  (*num)[x][y] = n;
}

void	key_left(int **num, int **ref, int y, int *ret)
{
  int	x;
  int	sv;

  x = 0;
  while (x < 4)
    {
      if (num[y][x] != 0)
	{
	  sv = x;
	  while (--sv >= 0)
	    {
	      if (num[y][sv] == 0)
		{
		  num[y][sv] = num[y][sv + 1];
		  num[y][sv + 1] = 0;
		  *ret = 1;
		}
	      else if (num[y][sv] == num[y][sv + 1] && !ref[y][sv] && !ref[y][sv + 1])
		{
		  num[y][sv] *= 2;
		  num[y][sv + 1] = 0;
		  ref[y][sv] = 1;
		  *ret = 1;
		}
	    }
	}
      x++;
    }
}

void	key_right(int **num, int **ref, int y, int *ret)
{
  int	x;
  int	sv;

  x = 4;
  while (--x >= 0)
      if (num[y][x] != 0)
	{
	  sv = x;
	  while (++sv < 4)
	      if (num[y][sv] == 0)
		{
		  num[y][sv] = num[y][sv - 1];
		  num[y][sv - 1] = 0;
		  *ret = 1;
		}
	      else if (num[y][sv] == num[y][sv - 1] 
		       && !ref[y][sv] && !ref[y][sv - 1])
		{
		  num[y][sv] *= 2;
		  num[y][sv - 1] = 0;
		  ref[y][sv] = 1;
		  *ret = 1;
		}
	}
}

void	key_up(int **num, int **ref, int y, int *ret)
{
  int	x;
  int	sv;

  x = 0;
  while (x < 4)
    {
      if (num[x][y] != 0)
	{
	  sv = x;
	  while (--sv >= 0)
	    {
	      if (num[sv][y] == 0)
		{
		  num[sv][y] = num[sv + 1][y];
		  num[sv + 1][y] = 0;
		  *ret = 1;
		}
	      else if (num[sv][y] == num[sv + 1][y] && !ref[sv][y] && !ref[sv + 1][y])
		{
		  num[sv][y] *= 2;
		  num[sv + 1][y] = 0;
		  ref[sv][y] = 1;
		  *ret = 1;
		}
	    }
	}
      x++;
    }
}

void	key_down(int **num, int **ref, int y, int *ret)
{
  int	x;
  int	sv;

  x = 3;
  while (x >= 0)
    {
      if (num[x][y] != 0)
	{
	  sv = x;
	  while (++sv < 4)
	    {
	      if (num[sv][y] == 0)
		{
		  num[sv][y] = num[sv - 1][y];
		  num[sv - 1][y] = 0;
		  *ret = 1;
		}
	      else if (num[sv][y] == num[sv - 1][y] && !ref[sv][y] && !ref[sv - 1][y])
		{
		  num[sv][y] *= 2;
		  num[sv - 1][y] = 0;
		  ref[sv][y] = 1;
		  *ret = 1;
		}
	    }
	}
      x--;
    }
}

void	dat(int **num, void (*f)(int **, int **, int, int *), int *ret)
{
  int	x;
  int	**ref;

  x = 0;
  if (!(ref = init_num()))
    malloc_error();
  set_init(ref);
  while (x < 4)
    {
      f(num, ref, x, ret);
      x++;
    }
  free_num(&ref);
}

void	add_nb(int **num)
{
  int	n;
  int	x;
  int	y;

  x = rand() % 4;
  y = rand() % 4;
  n = rand() % 2 == 0 ? 2 : 4;  
  while (num[x][y] != 0)
    {
      x = rand() % 4;
      y = rand() % 4;
    }
  num[x][y] = n;
}

int	key_handle(void *win, int ***num, t_swin *sw)
{
  int	key;
  int	ret;

  ret = 0;
  key = getch();
  if (key == 'q')
    return (1);
  else if (key == 'r')
    init_game(win, num, sw);
  else if (key == KEY_LEFT)
    dat(*num, &key_left, &ret);
  else if (key == KEY_RIGHT)
    dat(*num, &key_right, &ret);
  else if(key == KEY_UP)
    dat(*num, &key_up, &ret);
  else if (key == KEY_DOWN)
    dat(*num, &key_down, &ret);
  if (ret)
    add_nb(*num);
  return (0);
}

void	the_game(void *win, int ***num, t_swin *sw)
{
  while (1)
    {
      getmaxyx((WINDOW*)win, sw->y, sw->x);
      if (sw->x != sw->oldx || sw->y != sw->oldy)
	{
	  sw->oldx = sw->x;
	  sw->oldy = sw->y;
	  draw(win, sw, *num);
	}
      if (key_handle(win, num, sw) == 1)
	break ;
      draw(win, sw, *num);      
     }
}

int	main()
{
  void		*win;
  int		**num;
  t_swin	sw;

  if (!(win = init_curse()))
    return (0);
  if (!(num = init_num()))
    return (0);
  srand(time(NULL));
  init_game(win, &num, &sw);
  the_game(win, &num, &sw);
  free_num(&num);
  delwin(win);
  endwin();
  refresh();
  return (0);
}
