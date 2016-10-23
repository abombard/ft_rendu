/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:28:39 by abombard          #+#    #+#             */
/*   Updated: 2014/11/28 01:55:34 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_str_ptrs(char const **arg1, char const **arg2)
{
	const char *tmp;

	tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}

void	quicksort_strs(char const **args, unsigned int len)
{
	unsigned int	i;
	unsigned int	pvt;

	pvt = 0;
	if (len <= 1)
		return ;
	swap_str_ptrs(args + (len / 2), args + len - 1);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strcmp(args[i], args[len - 1]) < 0)
			swap_str_ptrs(args + i, args + pvt++);
		i++;
	}
	swap_str_ptrs(args + pvt, args + len - 1);
	quicksort_strs(args, pvt++);
	quicksort_strs(args + pvt, len - pvt);
}
