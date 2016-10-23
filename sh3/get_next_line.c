/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 17:41:30 by abombard          #+#    #+#             */
/*   Updated: 2014/12/29 16:47:40 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		*ft_buf_it(char **buf, int size, int x)
{
	char		*swap;

	if (!*buf)
		*buf = ft_strnew(size);
	else
	{
		if (!(swap = ft_strdup(*buf + x)))
			return (0);
		if (*buf)
			free(*buf);
		if (!(*buf = ft_strnew(size)))
			return (0);
		ft_strcpy(*buf, swap);
		if (swap)
			free(swap);
	}
	return (0);
}

static int		get_line(char **buf, char **line)
{
	char		*pb;
	int			x;

	x = 0;
	pb = *buf;
	while (*pb != '\n' && *pb != '\0')
		pb++, x++;
	if (*pb == '\n' || *pb == '\0')
	{
		*line = ft_strsub(*buf, 0, x);
		if (*pb == 0)
		{
			ft_strdel(buf);
			return (0);
		}
		ft_buf_it(buf, ft_strlen(*buf) - x, x + 1);
		return (1);
	}
	ft_strdel(buf);
	return (-1);
}

static int		ft_read(int const fd, char **line, char **bufcopy)
{
	int				ret;
	unsigned int	size;
	char			buf[BUFSIZE + 1];

	size = 0;
	while (*bufcopy && (*bufcopy)[size])
	{
		if ((*bufcopy)[size] == '\n' && get_line(bufcopy, line) == 1)
			return (1);
		size++;
	}
	while ((ret = read(fd, buf, BUFSIZE)) > 0)
	{
		buf[ret] = '\0';
		size += ret;
		ft_buf_it(bufcopy, size, 0);
		if (ft_strlcat(*bufcopy, buf, size + 1) < size || \
			ft_strchr(*bufcopy, '\n'))
			break ;
	}
	if (*bufcopy && get_line(bufcopy, line) == 1)
		return (1);
	return (ret);
}

static t_buf	*ft_buf_list(int fd)
{
	t_buf	*list;

	if (!(list = (t_buf*)malloc(sizeof(*list))))
		return (NULL);
	list->fd_ = fd;
	list->next = NULL;
	list->bufcopy = NULL;
	return (list);
}

int				get_next_line(int const fd, char **line)
{
	static t_buf	*list;
	t_buf			*tmp;

	if (BUFSIZE <= 0 || !line)
		return (-1);
	if (!list)
		if (!(list = ft_buf_list(fd)))
			return (-1);
	tmp = list;
	while (tmp)
	{
		if (tmp->fd_ == fd)
			return (ft_read(fd, line, &(tmp->bufcopy)));
		else if (tmp->next)
			tmp = tmp->next;
		else
		{
			if (!(tmp->next = ft_buf_list(fd)))
				return (-1);
			tmp = tmp->next;
			return (ft_read(fd, line, &(tmp->bufcopy)));
		}
	}
	return (-1);
}
