/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:06:27 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:08:17 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		run_redir(char **av)
{
	int		fd;
	char	*tmp;

	fd = -1;
	if (ft_strchr(av[0], '<') || ft_strchr(av[1], '<'))
	{
		tmp = av[0][0] == '<' ? av[1] : av[2];
		if ((fd = open(tmp, O_RDONLY, 0644)) == -1)
			return (-2);
		dup2(fd, 0);
	}
	else if (av[0][0] == '>' || av[1][0] == '>')
	{
		tmp = av[0][0] == '>' ? av[1] : av[2];
		if ((ft_strcmp(av[1], ">>") == 0 || ft_strcmp(av[0], ">>") == 0) \
			&& ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1))
			return (fd);
		if (fd == -1 \
			&& ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1))
			return (fd);
		dup2(fd, 1);
	}
	return (fd);
}

void	del_output(char ***tab, int x)
{
	char	**t;

	t = *tab;
	ft_strdel(&t[x + 1]);
	ft_strdel(&t[x + 2]);
	x += 3;
	while (t[x])
	{
		t[x - 2] = t[x];
		t[x] = NULL;
		x++;
	}
}

void	init_child_redir(char **cmd, t_list **env, int end)
{
	pid_t	child;
	int		fd;

	fd = -1;
	child = fork();
	if (child == -1)
		return (ft_putendl("fork error"));
	else if (child == 0)
	{
		fd = run_redir(&cmd[0]);
		close(fd);
		del_output(&cmd, 0);
		if (end == 1)
			init_shell(cmd[0], env);
		else if (cmd[0][0] != '<' && cmd[0][0] != '>')
			init_redir(cmd, env);
		exit(1);
	}
	wait(0);
	if (fd == -2)
		exit (1);
}

void	new_redir(char **cmd, t_list **env)
{
	int	x;

	ft_strdel(&cmd[1]);
	x = 2;
	while (cmd[x])
	{
		cmd[x - 1] = cmd[x];
		cmd[x] = NULL;
		x++;
	}
	return (init_redir(cmd, env));
}

void	init_redir(char **cmd, t_list **env)
{
	int	end;

	end = 0;
	if (!cmd)
		return ;
	if (cmd[0][0] == '<' || cmd[0][0] == '>')
		return (init_child_redir(cmd, env, 0));
	if (cmd[1][0] == '<' && cmd[1][1] == '<')
		return (new_redir(cmd, env));
	if (cmd[1][0] == '<')
		if (access(cmd[2], R_OK) == -1 && access(cmd[2], F_OK) == 0)
			return (access_error(cmd[2]));
	if (cmd[1][0] == '>')
		if (access(cmd[2], W_OK) == -1 && access(cmd[2], F_OK) == 0)
			return (access_error(cmd[2]));
	if (!cmd[3] && cmd[0][0] != '>' && cmd[0][0] != '<')
		end = 1;
	return (init_child_redir(cmd, env, end));
}
