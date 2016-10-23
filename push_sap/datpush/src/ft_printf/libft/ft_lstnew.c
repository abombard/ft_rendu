/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 09:35:19 by abombard          #+#    #+#             */
/*   Updated: 2014/11/08 10:14:00 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	content_size++;
	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	if (!(new->content = ft_memalloc(content_size)))
		return (NULL);
	new->next = NULL;
	if (content != NULL)
	{
		ft_memmove(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	return (new);
}
