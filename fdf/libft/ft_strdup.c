/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:26:14 by abombard          #+#    #+#             */
/*   Updated: 2014/11/04 12:21:05 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		size;

	size = ft_strlen(src);
	dest = (char*)malloc(sizeof(*src) * (size + 1));
	ft_strcpy(dest, src);
	return (dest);
}
