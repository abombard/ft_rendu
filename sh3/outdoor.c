/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdoor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:16:33 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:01:58 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		pipe_synth_error(char **line)
{
	char	*tmp;
	char	*buf;

	if (!(tmp = ft_strtrim(*line)))
		return (1);
	if (tmp[0] == '|')
	{
		ft_putendl_fd("synthax error near unexpected token '|'", 2);
		return (1);
	}
	if (tmp[ft_strlen(tmp) - 1] == '|')
	{
		while (get_next_line(0, &buf) > 0)
		{
			if (!(tmp = my_stradd(&tmp, buf, 0)))
				return (1);
			ft_strdel(&buf);
			ft_strdel(line);
			*line = tmp;
			return (0);
		}
	}
	ft_strdel(&tmp);
	return (0);
}

int		red_synth_error(char **line)
{
	char	*tmp;
	int		len;

	if (!(tmp = ft_strtrim(*line)))
		return (1);
	len = ft_strlen(tmp) - 1;
	if (tmp[len] == '>' || tmp[len] == '<')
	{
		ft_putendl_fd("synthax error near unexpected token 'newline'", 2);
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

int		redir(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int		bad_redir(char *line)
{
	int		x;
	int		y;
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (1);
	x = -1;
	y = 0;
	while (line[++x])
		if (!ft_isspace(line[x]))
			tmp[y++] = line[x];
	x = -1;
	while (tmp[++x])
		if ((redir(tmp[x]) && redir(tmp[x + 1])) \
			&& ((tmp[x] != tmp[x + 1]) || tmp[x] == '|'))
		{
			ft_putstr_fd("synthax error near unexpected token ", 2);
			ft_putchar_fd(tmp[x], 2);
			ft_putendl_fd("", 2);
			ft_strdel(&tmp);
			return (1);
		}
	ft_strdel(&tmp);
	return (0);
}

int		errors(char **line, t_list **env)
{
	if (pipe_synth_error(line) == 1)
		return (1);
	if (red_synth_error(line) == 1)
		return (1);
	if (bad_redir(*line) == 1)
		return (1);
	if (check_doubleinput(line, env) == 1)
		return (1);
	return (0);
}
