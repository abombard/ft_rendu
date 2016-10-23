/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 17:06:52 by abombard          #+#    #+#             */
/*   Updated: 2015/01/15 18:42:59 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     key_hook(int keycode, t_env *e)
{
    ft_putnbr(keycode);
    if (keycode == 65307)
        exit (1);
    if (keycode == 122)
        e->zoom *= 2;
    if (keycode == 120)
        e->zoom /= 2;
    if (keycode == 65363)
        e->moveX -= 0.1 / e->zoom;
    if (keycode == 65361)
        e->moveX += 0.1 / e->zoom;
    if (keycode == 65364)
        e->moveY -= 0.1 / e->zoom;
    if (keycode == 65362)
        e->moveY += 0.1 / e->zoom;
    if (keycode == 65508)
        e->maxIterations *= 2;
    if (keycode == 65406)
        e->maxIterations /= 2;
    if (keycode == 97)
        e->cIm += 0.01;
    if (keycode == 115)
        e->cIm -= 0.01;
    if (keycode == 113)
        e->cRe += 0.01;
    if (keycode == 119)
        e->cRe -= 0.01;
    if (keycode == 65457)
        e->mcolor = 0xffffff % (125 * 2);
    if (keycode == 65458)
        e->mcolor = 0xffff00 % (125 * 2);
    if (keycode == 65459)
        e->mcolor = 0xff0000 % (125 * 2);
    if (keycode == 65460)
        e->mcolor = 0xff0fff % (125 * 2);
	if (keycode == 32)
	{
		e->cRe = -0.7;
		e->cIm = 0.31021;
		e->Re = 0;
		e->Im = 0;
	}
    init_img(e);
    return (0);
}
