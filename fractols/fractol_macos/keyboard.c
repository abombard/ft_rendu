#include "fractol.h"

int	key_hook(int keycode, t_env *e)
{
  ft_putnbr(keycode);
  if (keycode == 53)
    exit (1);
  if (keycode == 6)
    e->zoom *= 2;
  if (keycode == 7)
    e->zoom /= 2;
  if (keycode == 123)
    e->moveX -= 0.1 / e->zoom;
  if (keycode == 124)
    e->moveX += 0.1 / e->zoom;
  if (keycode == 126)
    e->moveY -= 0.1 / e->zoom;
  if (keycode == 125)
    e->moveY += 0.1 / e->zoom;
  if (keycode == 258)
    e->maxIterations *= 2;
  if (keycode == 259)
    e->maxIterations /= 2;
  if (keycode == 0)
    e->cIm += 0.01;
  if (keycode == 1)
    e->cIm -= 0.01;
  if (keycode == 12)
    e->cRe += 0.01;
  if (keycode == 13)
    e->cRe -= 0.01;
  if (keycode == 83)
    e->mcolor = e->who == 2 ? 0x010101 : 0xffffff % (e->maxIterations * 2);
  if (keycode == 84)
    e->mcolor = e->who == 2 ? 0x010001 : 0xffff00 % (e->maxIterations * 2);
  if (keycode == 85)
    e->mcolor = e->who == 2 ? 0x010100 : 0xff0000 % (e->maxIterations * 2);
  if (keycode == 86)
    e->mcolor = e->who == 2 ? 0x000101 : 0xff0fff % (e->maxIterations * 2);
  if (keycode == 87)
    e->mcolor = e->who == 2 ? 0x000100 : 0xffffff / (e->maxIterations);
  init_img(e);
  return (0);
}
