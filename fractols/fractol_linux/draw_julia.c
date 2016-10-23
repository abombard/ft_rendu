/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 22:14:30 by abombard          #+#    #+#             */
/*   Updated: 2014/12/30 22:15:27 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		make_color(int r, int g, int b)
{
	int	ret;

	ft_memcpy((void*)&ret + 2, (void*)&r, 1);
	ft_memcpy((void*)&ret + 1, (void*)&g, 1);
	ft_memcpy((void*)&ret, (void*)&b, 1);
	return (ret);
}

void	draw_fractol(t_env *e, int x, int y)
{
	double	newRe;
	double	newIm;
	double	oldRe;
	double	oldIm;
	int	i;

	i = 0;
	newRe = 1.5 * (x - e->w / 2) / (0.5 * e->zoom * e->w) + e->moveX;
	newIm = (y - e->h / 2) / (0.5 * e->zoom * e->h) + e->moveY;
	while (i < e->maxIterations)
	{
		oldRe = newRe;
		oldIm = newIm;
		//the actual iteration, the real and imaginary part are calculated
		newRe = oldRe * oldRe - oldIm * oldIm + e->cRe;
		newIm = 2 * oldRe * oldIm + e->cIm;
		//if the point is outside the circle with radius 2: stop
		if ((newRe * newRe + newIm * newIm) > 4)
			break ;
		i++;
	}
/*
  intR;
  int G;
  int B;
  G = i > e->maxIterations ? 255 : (i * (255 % e->maxIterations));
  B = i > e->maxIterations ? 255 : (i * (255 % e->maxIterations));;
  R = 0;
  (void)G;
  (void)R;
  (void)B;
//e->color = make_color(R, G, B);
*/
	e->color = i > e->maxIterations ? 0xffffff : (i * (0xffffff % e->maxIterations));
	ft_memcpy(e->data + x * e->bpp / 8 + y * e->sizeline, &e->color, e->bpp / 8);
}

void	init_fractol(t_env *e)
{
	int	x;
	int	y;

	x = 0;
	while (x < e->w)
	{
		y = 0;
		while (y < e->h)
		{
			draw_fractol(e, x, y);
			y++;
		}
		x++;
	}
}

void	init_img(t_env *e)
{
	void	*img;

	if (!(img = mlx_new_image(e->mlx, e->w, e->h)))
		return ;
	if (!(e->data = mlx_get_data_addr(img, &e->bpp, &e->sizeline, &e->endian)))
		return ;
	init_fractol(e);
	mlx_put_image_to_window(e->mlx, e->win, img, 0, 0);
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	e->img = img;
}
