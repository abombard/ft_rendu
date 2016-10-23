/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 10:49:03 by abombard          #+#    #+#             */
/*   Updated: 2014/11/21 09:04:22 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*s_tmp;

	if (alst && del)
	{
		tmp = *alst;
		while (tmp)
		{
			s_tmp = tmp->next;
			ft_lstdelone(&tmp, del);
			tmp = s_tmp;
		}
		*alst = NULL;
	}
}
