/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 11:42:16 by abombard          #+#    #+#             */
/*   Updated: 2014/11/19 19:37:09 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int		x;

	x = 0;
	if (dst && src)
	{
		while (src[x])
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = '\0';
	}
	return (dst ? dst : NULL);
}
