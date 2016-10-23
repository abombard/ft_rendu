/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 11:20:06 by abombard          #+#    #+#             */
/*   Updated: 2015/03/25 14:06:59 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	if (lst && f)
	{
		tmp = f(ft_lstnew((void*)lst->content, lst->content_size));
		new = tmp;
		while (lst->next)
		{
			lst = lst->next;
			tmp->next = f(ft_lstnew((void*)lst->content, lst->content_size));
			tmp = tmp->next;
		}
	}
	return (new);
}
