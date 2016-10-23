/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:33:03 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:06:04 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		key_annexe(int keycode, t_env *e, int *bool, float c)
{
	if (keycode == 65307)
	{
		free_map(e->map, e->map_len.len, e->map_len.wid);
		free(e->img);
		exit (1);
	}
	if (keycode == 112)
	{
		*bool = 0;
		init_img(*e, NULL, &aff_parallele, c);
	}
	if (keycode == 99)
	{
		*bool = 1;
		init_img(*e, NULL, &aff_conique, c);
	}
}

static int		key_hook(int keycode, t_env *e)
{
	float		a;
	float		c;
	static int	bool;

	a = M_PI / 8;
	c = 2;
	key_annexe(keycode, e, &bool, c);
	if (keycode == 122)
		init_img(*e, &zoom, !bool ? &aff_parallele : &aff_conique, c);
	if (keycode == 120)
		init_img(*e, &zoom, !bool ? &aff_parallele : &aff_conique, -c);
	if (keycode == 65361)
		init_img(*e, &rot_matrice_z, !bool ? &aff_parallele : &aff_conique, a);
	if (keycode == 65363)
		init_img(*e, &rot_matrice_z, !bool ? &aff_parallele : &aff_conique, -a);
	if (keycode == 65362)
		init_img(*e, &rot_matrice_x, !bool ? &aff_parallele : &aff_conique, a);
	if (keycode == 65364)
		init_img(*e, &rot_matrice_x, !bool ? &aff_parallele : &aff_conique, -a);
	if (keycode == 65508)
		init_img(*e, &rot_matrice_y, !bool ? &aff_parallele : &aff_conique, a);
	if (keycode == 65506)
		init_img(*e, &rot_matrice_y, !bool ? &aff_parallele : &aff_conique, -a);
	return (0);
}

static int		expose_hook(t_env *e)
{
	int		z;

	z = 0;
	while (z * e->map_len.len < e->window.len / 3 \
			|| z * e->map_len.wid < e->window.len / 3)
		z++;
	while (z * e->map_len.len > e->window.len / 3 \
			|| z * e->map_len.wid > e->window.len / 3)
		z--;
	init_img(*e, &zoom, &aff_parallele, z);
	return (0);
}

static void		init_map(t_pos ***or_map, int len, int wid)
{
	t_pos	**map;
	int		x;
	int		y;
	int		c;

	c = 0x008800;
	map = *or_map;
	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < wid)
		{
			map[y][x].x -= wid / 2;
			map[y][x].y -= len / 2;
			map[y][x].color = map[y][x].z == 0 ? c : c - map[y][x].z * 2;
			x++;
		}
		y++;
	}
}

void			init_mlx(t_pos ***map, int line, int col)
{
	t_env	e;

	if (!*map)
	{
		ft_putendl("map error");
		return ;
	}
	e.window.len = 800;
	e.window.wid = 1296;
	e.map_len.len = line;
	e.map_len.wid = col;
	if (!(e.map = map))
		return ;
	init_map(e.map, e.map_len.len, e.map_len.wid);
	if (!(e.mlx = mlx_init()))
		return ;
	e.img = NULL;
	if (!(e.win = mlx_new_window(e.mlx, e.window.wid, e.window.len, "42")))
		return ;
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
}
