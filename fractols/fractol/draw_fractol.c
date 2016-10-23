/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/31 15:11:47 by abombard          #+#    #+#             */
/*   Updated: 2015/01/15 17:58:44 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_env *e, int x, int y)
{
	float	Re;
	float	Im;
	float	swap;
	int 	i;

	e->cRe = e->ratio * (x - e->w / 2) / (0.5 * e->zoom * e->w) + e->moveX;
	e->cIm = (y - e->h / 2) / (0.5 * e->zoom * e->h) + e->moveY;
	Re = e->Re;
	Im = e->Im;
	i = 0;
	while (i < e->maxIterations)
	{
		swap = Re;
		Re = swap * swap - Im * Im + e->cRe;
		Im = 2 * swap * Im + e->cIm;
		if ((Re * Re + Im * Im) > 4)
			break ;
		i++;
	}
	e->color = 12 * i * e->mcolor;
	ft_memcpy(e->data + x * e->bpp + y * e->sizeline, &e->color, e->bpp);
}

void	draw_julia(t_env *e, int x, int y)
{
	float	Re;
	float	Im;
	float	swap;
	int		i;

	i = -1;
	Re = e->ratio * (2 * x - e->w) / (e->zoom * e->w) + e->moveX;
	Im = (2 * y - e->h) / (e->zoom * e->h) + e->moveY;
	while (++i < e->maxIterations)
	{
		swap = Re;
		Re = swap * swap - Im * Im + e->cRe;
		Im = 2 * swap * Im + e->cIm;
		if ((Re * Re + Im * Im) > 4)
			break ;
	}
	e->color = e->mod * i * e->mcolor;
	ft_memcpy(e->data + x * e->bpp + y * e->sizeline, &e->color, e->bpp);
}

void	init_fractol(t_env *e, void (*f)(t_env *, int, int))
{
	int	x;
	int	y;

	x = 0;
	while (x < e->w)
	{
		y = 0;
		while (y < e->h)
		{
			f(e, x, y);
			y++;
		}
		x++;
	}
}

void	init_img(t_env *e)
{
	if (e->who == 0)
		init_fractol(e, &draw_julia);
	else if (e->who == 1)
		init_fractol(e, &draw_mandelbrot);
	else if (e->who == 2)
		draw_buddha(e);
	else
		exit (1);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}
