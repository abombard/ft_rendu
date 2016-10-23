/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:31:31 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:00:12 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	verif_setpix(int x, int y, t_env e, int coul)
{
	x += e.window.wid / 2;
	y += e.window.len / 2;
	if ((x >= 0 && x <= e.window.wid) && (y >= 0 && y <= e.window.len))
		ft_memcpy(e.data + x * e.bpp / 8 + y * e.sizeline, &coul, e.bpp / 8);
}

static void	int_switch(int *x, int *y)
{
	int	swap;

	swap = *x;
	*x = *y;
	*y = swap;
}

static void    	vertical(t_p pt1, t_p pt2, int coul, t_env e)
{
  int	d;
  int	aincr;
  int	bincr;
  int	incr;

  incr = pt2.sx > pt1.sx ? 1 : -1;
  d = 2 * fabs(pt2.sx - pt1.sx) - (pt2.sy - pt1.sy);
  aincr = 2 * (fabs(pt2.sx - pt1.sx) - (pt2.sy - pt1.sy));
  bincr = 2 * fabs(pt2.sx - pt1.sx);
  verif_setpix(pt1.sx, pt1.sy++, e, coul);
  while (++pt1.sy <= pt2.sy)
    {
      if (d >= 0)
	{
	  pt1.sx += incr;
	  d += aincr;
	}
      else
	d += bincr;
      verif_setpix(pt1.sx, pt1.sy, e, coul);
    }
}

static void	horizontal(t_p pt1, t_p pt2, int coul, t_env e)
{
  int	d;
  int	aincr;
  int	bincr;
  int	incr;

  incr = pt2.sy > pt1.sy ? 1 : -1;
  d = 2 * fabs(pt2.sy - pt1.sy) - (pt2.sx - pt1.sx);
  aincr = 2 * (fabs(pt2.sy - pt1.sy) - (pt2.sx - pt1.sx));
  bincr = 2 * fabs(pt2.sy - pt1.sy);
  verif_setpix(pt1.sx++, pt1.sy, e, coul);
  while (++pt1.sx <= pt2.sx)
    {
      if (d >= 0)
	{
	  pt1.sy += incr;
	  d += aincr;
	}
      else
	d += bincr;
      verif_setpix(pt1.sx, pt1.sy, e, coul);
    }
}

void		draw_line(t_p pt1, t_p pt2, int coul, t_env e)
{
  if (fabs(pt2.sx - pt1.sx) < fabs(pt2.sy - pt1.sy))
    {
      if (pt1.sy > pt2.sy)
	{
	  int_switch(&pt1.sx, &pt2.sx);
	  int_switch(&pt1.sy, &pt2.sy);
	}
      vertical(pt1, pt2, coul, e);
    }
  else
    {
      if (pt1.sx > pt2.sx)
	{
	  int_switch(&pt1.sx, &pt2.sx);
	  int_switch(&pt1.sy, &pt2.sy);
	}
      horizontal(pt1, pt2, coul, e);
    }
}
