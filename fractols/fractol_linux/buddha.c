/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 18:13:35 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 22:42:13 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	find_buddha(t_env *e, unsigned **tab)
{
  float   swap;
  int     i;
  int	x;
  int	y;

  e->Re = 0;
  e->Im = 0;
  i = 0;
  while (i < e->maxIterations)
  {
      swap = e->Re;
      e->Re = swap * swap - e->Im * e->Im + e->cRe;
      e->Im = 2 * swap * e->Im + e->cIm;
      x = (e->Im * e->w / (4 / e->zoom)) + e->w / 2;
      y = e->ratio * (e->Re * e->h / (4 / e->zoom)) + e->h / 2 + e->h / 5.5;
      if ((e->Re * e->Re + e->Im * e->Im) > 4)
		  break ;
      else if ((x < e->w && x > 0) && (y > 0 && y < e->h))
	{
	  tab[x][y] += tab[x][y] >= e->mcolor * 224 ? 0 : e->mcolor;
	}
      i++;
  }
}

void    buddha(t_env *e, unsigned int **tab)
{
  float   swap;
  int     i;

  e->cRe = -2;
  while (e->cRe < 2)
  {
	  e->cIm = -2;
	  while (e->cIm < 2)
	  {
		  e->Re = 0;
		  e->Im = 0;
		  i = -1;
		  while (++i < e->maxIterations)
		  {
			  swap = e->Re;
			  e->Re = swap * swap - e->Im * e->Im + e->cRe;
			  e->Im = 2 * swap * e->Im + e->cIm;
			  if ((e->Re * e->Re + e->Im * e->Im) > 4)
				  break ;
		  }
		  if (i < e->maxIterations)
			  find_buddha(e, tab);
		  e->cIm += e->inc;
	  }
	  e->cRe += e->inc;
  }
}

unsigned int	**init_tab(int w, int h)
{
	unsigned int	**tab;
	unsigned int	*tab2;
	int				x;

	x = 0;
	if (!(tab = (unsigned int **)malloc(sizeof(*tab) * w)))
		return (NULL);
	if (!(tab2 = (unsigned int *)malloc(sizeof(tab) * w * h)))
		return (NULL);
	while (x < w)
	{
		tab[x] = &tab2[x * h];
		x++;
	}
	return (tab);
}

void	draw_buddha(t_env *e)
{
	unsigned int	**tab;
	int				i;
	int				j;

	if (!(tab = init_tab(e->w, e->h)))
		return (ft_putendl("malloc error"));
	i = -1;
	while (++i < e->w)
	{
		j = -1;
		while (++j < e->h)
			tab[i][j] = 0;
	}
	buddha(e, tab);
	i = -1;
	while (++i < e->w)
	{
		j = -1;
		while (++j < e->h)
			ft_memcpy(e->data + i * e->bpp + j * e->sizeline,	\
					  &(tab[i])[j], e->bpp);
	}
	free(tab[0]);
	free(tab);
}
