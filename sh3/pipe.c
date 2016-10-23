/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 15:02:27 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:04:02 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	run_pipe(char **cmd, t_list **env)
{
	pid_t	cpid;
	int		pipefd[2];

	pipe(pipefd);
	cpid = fork();
	if (cpid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (ft_putendl_fd("fork error", 2));
	}
	else if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		redirection(cmd[0], env);
		exit(1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	wait(0);
	cmd[2] ? init_child_pipe(&cmd[1], env) : redirection(cmd[1], env);
	exit(1);
}

void	init_child_pipe(char **cmd, t_list **env)
{
	pid_t child;

	child = fork();
	if (child == -1)
		return (ft_putendl("fork error"));
	else if (child == 0)
	{
		run_pipe(cmd, env);
		exit (1);
	}
	wait(0);
}

void	init_pipe(char **sp, t_list **env)
{
	return (init_child_pipe(sp, env));
}
