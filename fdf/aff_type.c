/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:36:40 by abombard          #+#    #+#             */
/*   Updated: 2014/12/10 19:37:20 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_p		aff_conique(t_pos pt)
{
	t_p	ret;
	int	f;
	int	size;

	f = 850;
	size = 250;
	ret.sx = size + (pt.x - size) * f / (pt.z + f);
	ret.sy = size + (pt.y - size) * f / (pt.z + f);
	ret.color = pt.color;
	return (ret);
}

t_p		aff_parallele(t_pos pt)
{
	t_p	ret;

	ret.sx = pt.x;
	ret.sy = pt.y;
	ret.color = pt.color;
	return (ret);
}
