/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dlinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 14:49:00 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 14:56:16 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		readinput(char *trig, int fd)
{
	char	*buf;

	buf = NULL;
	ft_putstr("> ");
	while (get_next_line(0, &buf) > 0)
	{
		if (ft_strcmp(trig, buf) == 0)
		{
			ft_strdel(&buf);
			return (0);
		}
		ft_putstr("> ");
		ft_putendl_fd(buf, fd);
		ft_strdel(&buf);
	}
	return (0);
}

char	*doubleinput(char **line)
{
	char	buf[32];
	char	*tmp;
	int		x;
	int		i;

	i = 0;
	x = -1;
	tmp = *line;
	while (tmp[++x])
		if (tmp[x] == '<' && tmp[x + 1] == '<' && !betw_char(tmp, x, '"'))
			break ;
	if (!tmp[x])
		return (NULL);
	tmp[x++] = ' ';
	tmp[x++] = ' ';
	while (tmp[x] && ft_isspace(tmp[x]))
		x++;
	while (tmp[x] && ft_isalnum(tmp[x]))
	{
		buf[i++] = tmp[x];
		tmp[x++] = ' ';
	}
	buf[i] = 0;
	return (ft_strdup(buf));
}

void	child_doubleinput(char **cmd, t_list **env)
{
	pid_t	child;
	char	*trig;
	int		pi[2];

	pipe(pi);
	if (!cmd)
		return ;
	child = fork();
	if (child == -1)
		return (ft_putendl("fork error"));
	else if (child == 0)
	{
		close(pi[0]);
		if ((trig = doubleinput(cmd)))
			readinput(trig, pi[1]);
		ft_strdel(&trig);
		exit(1);
	}
	close(pi[1]);
	dup2(pi[0], 0);
	wait(0);
	trig = doubleinput(cmd);
	ft_strdel(&trig);
	split_cmd(*cmd, env);
	exit (1);
}

void	init_child_doubleinput(char **cmd, t_list **env)
{
	pid_t child;

	child = fork();
	if (child == -1)
		return (ft_putendl("fork error"));
	else if (child == 0)
	{
		child_doubleinput(cmd, env);
		exit (1);
	}
	wait(0);
}

int		check_doubleinput(char **line, t_list **env)
{
  char	*pt;
  int	x;

  pt = *line;
  x = 0;
  while (pt[x])
    {
      if (pt[x] == '<' && pt[x + 1] == '<')
	{
	  init_child_doubleinput(line, env);
	  if ((pt = doubleinput(line)))
	    ft_strdel(&pt);
	  check_doubleinput(line, env);
	  return (1);
	}
      x++;
    }
  return (0);
}
