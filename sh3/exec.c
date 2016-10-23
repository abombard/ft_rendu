/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 22:07:37 by abombard          #+#    #+#             */
/*   Updated: 2015/02/23 19:27:56 by abombard         ###   ########.fr       */
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

void		out_of_path(char **av, char **env)
{
	char	*bin;
	int		x;

	x = 0;
	bin = av[0];
	if (bin[0] == '.' && bin[1] == '/')
	{
		execve(&bin[2], av, env);
	}
	x = 0;
	while (av[x])
	{
		ft_putstr_fd(av[x++], 2);
		if (av[x])
		  ft_putchar_fd(' ', 2);
	}
	ft_putendl_fd(": command not found", 2);
}

void		execute(char **path, char **av, char **env)
{
	char	*execpath;
	char	*join;
	int		x;

	x = -1;
	join = NULL;
	execpath = NULL;
	if (access(av[0], F_OK) != -1)
	{
		execve(av[0], av, env);
		return ;
	}
	while (path[++x])
	{
		if (!(join = ft_strjoin(path[x], "/")) \
			|| !(execpath = ft_strjoin(join, av[0])))
			return (ft_putendl_fd("malloc error", 2));
		if (access(execpath, F_OK) == -1)
			continue ;
		if (access(execpath, X_OK) == -1)
		{
			access_error(execpath);
			ft_strdel(&join);
			return (ft_strdel(&execpath));
		}
		execve(execpath, av, env);
		ft_strdel(&join);
		ft_strdel(&execpath);
	}
	out_of_path(av, env);
}

int			list_len(t_list **env)
{
	t_list	*tmp;
	int		x;

	x = 0;
	tmp = *env;
	while (tmp)
	{
		x += 1;
		tmp = tmp->next;
	}
	return (x);
}

char		**list_to_tab(t_list **env)
{
	t_list *tmp;
	char	**tab;
	int		len;

	len = list_len(env);
	tmp = *env;
	if (!(tab = malloc(sizeof(char*) * len)))
		return (NULL);
	len = 0;
	while (tmp)
	{
		tab[len++] = tmp->content;
		tmp = tmp->next;
	}
	tab[len] = 0;
	return (tab);
}

void		env_fun(char **av, t_list **o_env)
{
	pid_t	father;
	char	**path;
	char	**tenv;
	t_list	*env;
	int		x;

	if (!(tenv = list_to_tab(o_env)))
		ft_putendl_fd("couldnt build char **env", 2);;
	env = *o_env;
	if (!(path = get_path(env)))
		return (ft_putendl_fd("Path not found or Ineffective", 2));
	if ((father = fork()) > 0)
		wait(0);
	if (father == 0)
	{
		execute(path, av, tenv);
		exit (0);
	}
	x = 0;
	while (path[x])
		ft_strdel(&path[x++]);
	free(path);
	if (tenv)
		free(tenv);
}
