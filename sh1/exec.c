/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 22:07:37 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 22:11:47 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static char	**get_path(t_list *env)
{
	t_list	*tmp;
	char	**path;
	char	*temp;

	temp = NULL;
	path = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
		{
			if (!(temp = ft_strdup(ft_strchr(tmp->content, '=') + 1)))
				return (NULL);
			if (!(path = ft_strsplit(temp, ':')))
				return (NULL);
			ft_strdel(&temp);
		}
		tmp = tmp->next;
	}
	return (path);
}

void		execute(char **path, char **av)
{
	char	*execpath;
	char	*join;
	int		x;

	x = -1;
	join = NULL;
	execpath = NULL;
	while (path[++x])
	{
		if (!(join = ft_strjoin(path[x], "/")))
			return (ft_putendl("malloc error"));
		if (!(execpath = ft_strjoin(join, av[0])))
			return (ft_putendl("malloc error"));
		execve(execpath, av, NULL);
		ft_strdel(&join);
		ft_strdel(&execpath);
	}
	execve(av[0], av, NULL);
	x = 0;
	while (av[x])
	{
		ft_putstr_fd(av[x++], 2);
		ft_putchar(' ');
	}
	ft_putendl_fd(": command not found", 2);
}

void		env_fun(char **av, t_list **o_env)
{
	pid_t	father;
	char	**path;
	t_list	*env;
	int		x;

	env = *o_env;
	if (!(path = get_path(env)))
		return (ft_putendl_fd("Path not found or Ineffective", 2));
	if ((father = fork()) > 0)
		wait(0);
	if (father == 0)
	{
		execute(path, av);
		exit (0);
	}
	x = 0;
	while (path[x])
		ft_strdel(&path[x++]);
	free(path);
}
