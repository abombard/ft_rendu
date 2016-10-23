/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:15:52 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:16:18 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_stradd(char **s1, char **s2, int len)
{
	char	*ret;
	int		length;

	ret = NULL;
	if (s2)
	{
		if (len == 0)
			len = ft_strlen(*s2);
		length = s1 ? ft_strlen(*s1) + ft_strlen(*s2) : ft_strlen(*s2);
		ret = ft_strnew(length + 1);
		if (s1)
			ft_strlcat(ret, *s1, ft_strlen(*s1) + 1);
		len += 1;
		ft_strlcat(ret, *s2, s1 ? ft_strlen(*s1) + len : len);
		ft_strdel(s1);
	}
	return (ret);
}
