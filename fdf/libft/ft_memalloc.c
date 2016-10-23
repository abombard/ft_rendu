/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:22:20 by abombard          #+#    #+#             */
/*   Updated: 2014/11/21 09:10:47 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char	*str;
	int		x;

	x = 0;
	if (!(str = (char*)malloc(sizeof(str) * size)))
		return (NULL);
	while (size--)
		str[x++] = 0;
	return ((void*)str);
}
