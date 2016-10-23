/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 19:43:45 by abombard          #+#    #+#             */
/*   Updated: 2015/02/04 19:45:35 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_stradd(char **s1, char *s2, int len)
{
	char	*ret;
	int		length;

	ret = NULL;
	if (s2)
    {
		length = s1 && *s1 ? ft_strlen(*s1) + ft_strlen(s2) : ft_strlen(s2);
		ret = ft_strnew(length + 1);
		if (s1 && *s1)
			ft_strlcat(ret, *s1, ft_strlen(*s1) + 1);
		if (len)
		{
			len += 1;
			ft_strlcat(ret, s2, s1 && *s1 ? ft_strlen(*s1) + len : len);
		}
		else
			ft_strlcat(ret, s2, length + 1);
		ft_strdel(s1);
    }
	return (ret);
}
