/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:29:47 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 22:06:51 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pos		rot_matrice_x(t_pos pt, float a)
{
	t_pos	ret;

	ret.x = pt.x;
	ret.y = pt.y * cos(a) + pt.z * -sin(a);
	ret.z = pt.y * sin(a) + pt.z * cos(a);
	ret.color = pt.color;
	return (ret);
}

t_pos		rot_matrice_y(t_pos pt, float a)
{
	t_pos	ret;

	ret.x = pt.x * cos(a) + pt.z * sin(a);
	ret.y = pt.y;
	ret.z = pt.x * -sin(a) + pt.z * cos(a);
	ret.color = pt.color;
	return (ret);
}

t_pos		rot_matrice_z(t_pos pt, float a)
{
	t_pos	ret;

	ret.x = pt.x * cos(a) + pt.y * -sin(a);
	ret.y = pt.x * sin(a) + pt.y * cos(a);
	ret.z = pt.z;
	ret.color = pt.color;
	return (ret);
}

t_pos		zoom(t_pos pt, float c)
{
	if (c > 0)
	{
		pt.x *= c;
		pt.y *= c;
		pt.z *= c;
	}
	else if (c < 0)
	{
		pt.x /= -c;
		pt.y /= -c;
		pt.z /= -c;
	}
	return (pt);
}
