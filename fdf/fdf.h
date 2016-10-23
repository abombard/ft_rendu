/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 23:12:41 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:02:40 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include "get_next_line.h"
#include <mlx.h>
#include <unistd.h>
#include <math.h>

typedef struct  s_pos
{
    float		x;
    float		y;
    float		z;
	int			color;
}               t_pos;

typedef struct	s_p
{
  int	sx;
  int	sy;
  int	color;
}		t_p;

typedef struct			s_lst
{
	int				x;
	int				y;
	int				z;
	struct s_lst	*next;
}				t_lst;

typedef struct	s_s
{
	int		len;
	int		wid;
}				t_s;

typedef struct  s_env
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
	t_pos	***map;
	t_s		map_len;
	t_s		window;
  
}               t_env;

t_p			aff_conique(t_pos pt);
t_p			aff_parallele(t_pos pt);
t_pos		rot_matrice_x(t_pos pt, float a);
t_pos		rot_matrice_y(t_pos pt, float a);
t_pos		rot_matrice_z(t_pos pt, float a);
t_pos		zoom(t_pos pt, float a);
void		draw_line(t_p pt1, t_p pt2, int coul, t_env e);
t_p     	**build_tab(int len, int col);
void		draw_map(t_env e, t_pos (*f)(t_pos, float), t_p (*p)(t_pos), float a);
void		init_img(t_env e, t_pos (*f)(t_pos, float), t_p (*p)(t_pos), float a);
void		init_mlx(t_pos ***map, int line, int col);
void		free_map(t_pos ***or_map, int len, int col);

#endif
