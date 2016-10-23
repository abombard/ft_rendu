/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 23:12:25 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:04:20 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			free_map(t_pos ***or_map, int len, int col)
{
	t_pos	**map;
	int		x;

	(void)col;
	map = NULL;
	map = *or_map;
	x = 0;
	if (map)
	{
		while (x < len)
		{
			if (map[x])
				free(map[x]);
			x++;
		}
		free(map);
		map = NULL;
	}
	exit (1);
}

static t_pos	*add_line(char ***or_tab, int len, int *col)
{
	char	**tab;
	t_pos	*new_line;
	int		x;

	x = 0;
	tab = *or_tab;
	while (tab[x])
		x++;
	if (*col == 0)
		*col = x;
	if (x != *col)
		return (NULL);
	if (!(new_line = (t_pos*)malloc(sizeof(t_pos) * x)))
		return (NULL);
	x = 0;
	while (tab[x])
	{
		new_line[x].x = x;
		new_line[x].y = len;
		new_line[x].z = ft_atoi(tab[x]);
		free(tab[x++]);
	}
	free(tab);
	return (new_line);
}

static t_pos	**build_map(t_pos ***or_map, char *line, int len, int *col)
{
	char	**tab;
	t_pos	**map;
	int		x;

	while (ft_isdigit(line[x]) == 1 || line[x] == ' ' || line[x] == '-')
		x++;
	if (line[x] != 0)
		return (NULL);
	if (!(tab = ft_strsplit(line, ' ')))
	  return (NULL);
	if (!(map = (t_pos**)malloc(sizeof(t_pos*) * (len + 1))))
		return (NULL);
	if (*or_map)
	{
		x = 0;
		while (x < len)
		{
			map[x] = (*or_map)[x];
			x++;
		}
		free(*or_map);
	}
	map[len] = add_line(&tab, len, col);
	return (map);
}

int				main(int ac, char **av)
{
	t_pos	**map;
	char	*line;
	int		len;
	int		col;

	len = 0;
	col = 0;
	map = NULL;
	if (ac == 2 && (ac = open(av[1], O_RDONLY)) != -1)
	{
		while (get_next_line(ac, &line) > 0)
		{
			if (!(map = build_map(&map, line, len++, &col)) || !map[len - 1])
			{
				ft_putendl("map error");
				free_map(&map, len, col);
			}
			ft_strdel(&line);
		}
		close(ac);
		init_mlx(&map, len, col);
	}
	else
		ft_putendl("Use : ./fdf [map file]");
	return (0);
}
