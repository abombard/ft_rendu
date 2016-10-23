/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 22:13:03 by abombard          #+#    #+#             */
/*   Updated: 2014/12/31 19:36:16 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
  float xLast;
  float yLast;

#include <stdio.h>
  printf("Here = %.6f\n", e->xscreen);
  printf("Here = %.6f\n", e->yscreen);
  if (button == 1)
    e->motion = 1;
  if (button == 3)
    e->motion = 0;
  if (button == 4)
    {
      xLast = e->ratio * (2 * x - e->w) / (e->zoom * e->w);
      yLast = (2 * y - e->h) / (e->zoom * e->h);
      e->zoom *= 2;
      e->moveX += (xLast - e->xscreen) - (xLast / 2 - e->xscreen);
      e->moveY += (yLast - e->yscreen) - (yLast / 2 - e->yscreen);
    }
  if (button == 5)
    {
      xLast = e->ratio * (2 * x - e->w) / (e->zoom * e->w);
      yLast = (2 * y - e->h) / (e->zoom * e->h);
      e->zoom /= 2;
      e->moveX += (xLast - e->xscreen) - (xLast * 2 - e->xscreen);
      e->moveY += (yLast - e->yscreen) - (yLast * 2 - e->yscreen);
    }
  init_img(e);
  return (0);
}

int		expose_hook(t_env *e)
{
  mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
  return (0);
}

int	motion_event(int x, int y, t_env *e)
{
  int buffer[2];
 
  if (e->motion && ((buffer[0] != x && (buffer[0] < x - 50 || buffer[0] > x + 50))
		    || (buffer[1] != y && (buffer[1] < y - 50 || buffer[1] > y + 50))))
    {
      if (buffer[0] != x && (buffer[0] < x - 50 || buffer[0] > x + 50))
	{
	  e->cIm += x > buffer[0] ? 0.01 : -0.01;
	  e->Im += x > buffer[0] ? 0.1 : -0.1;
	}
      if (buffer[1] != y && (buffer[1] < y - 50 || buffer[1] > y + 50))
	{
	  e->cRe += y > buffer[1] ? 0.01 : -0.01;
	  e->Re += y > buffer[1] ? 0.1 : -0.1;
	  init_img(e);
	}
      init_img(e);
      buffer[0] = x;
      buffer[1] = y;
    }
  return (0);
}

void	init_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
	  return (ft_putendl_fd("failed to init mlx", 2));
	if (e->who == 0 && !(e->win = mlx_new_window(e->mlx, e->w, e->h, "Julia Explorer")))
	  return (ft_putendl_fd("failed to init window", 2));
	else if (e->who == 1 && !(e->win = mlx_new_window(e->mlx, e->w, e->h, "Mandelbrot Explorer")))
	  return (ft_putendl_fd("failed to init window", 2));
	else if (e->who == 2 && !(e->win = mlx_new_window(e->mlx, e->w, e->h, "Buddha Explorer")))
	  return (ft_putendl_fd("failed to init window", 2));
	if (!(e->img = mlx_new_image(e->mlx, e->w, e->h)))
	  return (ft_putendl_fd("failed to init img", 2));
	if (!(e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian)))
	  return (ft_putendl_fd("failed to get img adress", 2));
	e->bpp /= 8;
	mlx_key_hook(e->win, key_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 6, 1 << 6, motion_event, e);
	mlx_expose_hook(e->win, expose_hook, e);
	init_img(e);
	mlx_loop(e->mlx);
}
