/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 17:50:55 by abombard          #+#    #+#             */
/*   Updated: 2014/12/31 19:21:03 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_env(t_env *e)
{
    e->ratio = e->h / (float)(e->w / 2);
    e->Re = 0;
    e->Im = 0;
    e->zoom = 1;
    e->moveX = 0;
    e->moveY = 0;
    e->motion = 0;
    e->mod = 6;
    if (e->who != 2)
      {
	e->cRe = -0.7;
	e->cIm = 0.31021;
	e->maxIterations = 30;
	e->mcolor = 0xffffff % (125 * 2);
      }
    else
      {
	e->maxIterations = 500;
	e->mcolor = 0x010101;
	e->inc = 0.001;
      }
    init_mlx(e);
}

void	backdoor(void)
{
  ft_putendl("Use : ./fractol [M | J | B] (optional : [size: 1, 2, 3, 4] or [Height] [Width])");
  exit (1);
}

void	check_errors(int ac, char **av)
{
  if (ac == 2 || ac == 3 || ac == 4)
    {
      if ((ac == 3 && ft_atoi(av[2]) > 0 && ft_atoi(av[2]) < 5)	  \
	  || (ac == 4 && ft_atoi(av[2]) > 0 && ft_atoi(av[3]) > 0 \
	      && ft_atoi(av[2]) < 1500 && ft_atoi(av[3]) < 2000))
	{
	  (void)ac;
	}
      else if (ac == 3 || ac == 4)
	backdoor();
      if (ft_strcmp(av[1], "J") == 0 || ft_strcmp(av[1], "M") == 0 || ft_strcmp(av[1], "B") == 0)
	ft_putendl("Valid argument, program starting..");
      else
	backdoor();
    }
  else
    backdoor();
}

int 	main(int ac, char **av)
{   
  t_env	e;

  check_errors(ac, av);
  e.h = 900;
  e.w = 1200;
  if (ac == 3 || ac == 4)
    {
      e.h = ac == 4 ? ft_atoi(av[2]) : ft_atoi(av[2]) * 300;
      e.w = ac == 4 ? ft_atoi(av[3]) : ft_atoi(av[2]) * 400;
    }
  if (ft_strcmp(av[1], "J") == 0)
    e.who = 0;
  else if (ft_strcmp(av[1], "M") == 0)
    e.who = 1;
  else if (ft_strcmp(av[1], "B") == 0)
    e.who = 2;
  init_env(&e);
  return (0);
}
