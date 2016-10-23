/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 22:13:03 by abombard          #+#    #+#             */
/*   Updated: 2015/01/15 18:42:06 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
	if (button == 1)
		e->motion = 1;
	if (button == 3)
		e->motion = 0;
	if (button == 4)
	{
		e->moveX = (x - e->w / 2) / (e->w / 2);
		e->moveY = (y - e->h / 2) / (e->h / 2);
		e->zoom *= 2;
	}
	if (button == 5)
	{
		e->zoom /= 2;
	}
	init_img(e);
	return (0);
}

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		motion_event(int x, int y, t_env *e)
{
	if (e->motion)
	{
		e->cIm += x > e->buf[0] ? 0.01 : -0.01;
		e->Im += x > e->buf[0] ? 0.01 : -0.01;
		e->cRe += y > e->buf[1] ? 0.01 : -0.01;
		e->Re += y > e->buf[1] ? 0.01 : -0.01;
		e->buf[0] = x;
		e->buf[1] = y;
	}
	return (0);
}

int		loop_hook(t_env *e)
{
	static int		trig[2];

	if (trig[0] != e->buf[0] || trig[1] != e->buf[1] || e->buf[0] == 0)
	{
		init_img(e);
		trig[0] = e->buf[0];
		trig[1] = e->buf[1];
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
		return ft_putendl_fd("failed to init img", 2);
	if (!(e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian)))
		return ft_putendl_fd("failed to get img adress", 2);
	e->bpp /= 8;
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, key_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 6, 1 << 6, motion_event, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
