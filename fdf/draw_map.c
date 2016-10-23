/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:35:19 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:01:36 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_p		**build_tab(int len, int col)
{
	t_p		**tab;
	t_p		*tab2;
	int		x;

	x = 0;
	if (!(tab = (t_p**)malloc(sizeof(*tab) * len)))
		return (NULL);
	if (!(tab2 = (t_p*)malloc(sizeof(*tab2) * len * col)))
		return (NULL);
	while (x < len)
	{
		tab[x] = &tab2[x * col];
		x++;
	}
	return (tab);
}

void	draw_map(t_env e, t_pos (*f)(t_pos, float), t_p (*p)(t_pos), float a)
{
	int		x;
	int		y;
	t_pos	**map;
	t_p		**tmp;

	map = *e.map;
	if (!(tmp = build_tab(e.map_len.len, e.map_len.wid)))
		return ;
	y = -1;
	while (++y < e.map_len.len)
	{
		x = -1;
		while (++x < e.map_len.wid)
		{
			if (f)
				map[y][x] = f(map[y][x], a);
			tmp[y][x] = p(map[y][x]);
			if (x > 0)
				draw_line(tmp[y][x - 1], tmp[y][x], tmp[y][x].color, e);
			if (y > 0)
				draw_line(tmp[y - 1][x], tmp[y][x], tmp[y][x].color, e);
		}
	}
	free(tmp[0]);
	free(tmp);
}

void	init_img(t_env e, t_pos (*f)(t_pos, float), t_p (*p)(t_pos), float a)
{
	void	*img;

	if (!(img = mlx_new_image(e.mlx, e.window.wid, e.window.len)))
		return ;
	e.data = mlx_get_data_addr(img, &e.bpp, &e.sizeline, &e.endian);
	draw_map(e, f, p, a);
	mlx_put_image_to_window(e.mlx, e.win, img, 0, 0);
	if (e.img)
		free(e.img);
	e.img = img;
}
