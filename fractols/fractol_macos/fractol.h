/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 17:59:46 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 18:53:36 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				w;
	int				h;
  float			ratio;
	float			Re;
	float			Im;
	float			cRe;
	float			cIm;
	float			zoom;
	float			moveX;
	float			moveY;
	int				maxIterations;
	unsigned int				color;
	unsigned int	mcolor;
	int				who;
	float			inc;
  int			motion;
  int			mod;
}				t_env;

void	draw_buddha(t_env *e);
void	init_img(t_env *e);
void	init_mlx(t_env *e);
int	key_hook(int keycode, t_env *e);

#endif
