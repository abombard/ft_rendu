/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:59:45 by abombard          #+#    #+#             */
/*   Updated: 2014/11/28 08:53:12 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFSIZE 100

typedef struct	s_buf
{
	char			*bufcopy;
	int				fd_;
	struct s_buf	*next;
}				t_buf;

int				get_next_line(int const fd, char **line);

#endif
