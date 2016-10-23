/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 22:23:10 by abombard          #+#    #+#             */
/*   Updated: 2014/11/21 09:09:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*make_nbr(char *nbr, long long n, int len)
{
	if (n < 0)
	{
		nbr[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		nbr[0] = '0';
	while (n > 0)
	{
		nbr[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (nbr);
}

char			*ft_itoa(int n)
{
	char		*nbr;
	long long	save;
	int			len;

	len = 0;
	save = (long long)n;
	if (save < 0)
	{
		len++;
		save = save * -1;
	}
	while (save > 0)
	{
		save = save / 10;
		len++;
	}
	if (!(nbr = (char*)ft_memalloc(len + 1)))
		return (NULL);
	nbr[len + 1] = '\0';
	nbr = make_nbr(nbr, (long long)n, len);
	return (nbr);
}
