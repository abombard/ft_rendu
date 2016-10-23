/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:03:50 by abombard          #+#    #+#             */
/*   Updated: 2014/11/19 19:44:44 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			x;

	if (!s1 || !s2 || !n)
		return (0);
	x = 0;
	while (s1[x] == s2[x] && s1[x] && s2[x] && x < n)
		x++;
	if (x == n)
		return (0);
	else if (s1[x] != s2[x])
	{
		s1 += x;
		s2 += x;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
