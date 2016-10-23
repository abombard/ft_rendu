#include "fractol.h"

int		colors(int keycode, t_env *e)
{
  if (keycode == 38)
    {
      e->mcolor = e->who == 2 ? 0x010101 : 0xffffff % (125 * 2);
      e->mod = 6;
    }
  else if (keycode == 233)
    {
      e->mcolor = e->who == 2 ? 0x010001 : 0xffff00 % (125 * 2);
      e->mod = 5;
    }
  else if (keycode == 34)
    {
      e->mcolor = e->who == 2 ? 0x000101 : 0xff0000 % (125 * 2);
      e->mod = 6;
    }
  else if (keycode == 39)
    {
      e->mcolor = e->who == 2 ? 0x010000 : 0xff0fff % (125 * 2);
      e->mod = 20;
    }
  else if (keycode == 40)
      e->mcolor = e->who == 2 ? 0x000100 : 0xff0000 / 125 * 2;
  else
    return (0);
  return (1);
}

int             key_hook(int keycode, t_env *e)
{
  if (keycode == 65307)
    exit (1);
  else if (keycode == 65363)
      e->moveX += 0.2 / e->zoom;
  else if (keycode == 65361)
      e->moveX -= 0.2 / e->zoom;
  else if (keycode == 65364)
      e->moveY += 0.2 / e->zoom;
  else if (keycode == 65362)
      e->moveY -= 0.2 / e->zoom;
  else if (keycode == 33)
      e->maxIterations *= 2;
  else if (keycode == 58)
      e->maxIterations /= 2;
  else if (colors(keycode, e) == 0)
    {
      ft_putnbr(keycode);
      ft_putchar('\n');
      return (0);
    }
  init_img(e);
  return (0);
}
