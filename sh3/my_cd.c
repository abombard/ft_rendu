/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 13:44:13 by abombard          #+#    #+#             */
/*   Updated: 2015/02/07 20:12:33 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	case1(t_list *env)
{
	t_list	*tmp;
	char	*path;

	tmp = NULL;
	path = NULL;
	tmp = env;
	while (tmp && ft_strncmp("OLDPWD=", tmp->content, 7) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		path = ft_strchr(tmp->content, '=') + 1;
		if (chdir(path) == 0)
			ft_putendl(path);
	}
	else
		access_error(path);
}

void	case2(t_list *env)
{
	t_list	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	tmp = env;
	while (tmp && ft_strncmp(tmp->content, "HOME=", 5) != 0)
		tmp = tmp->next;
	if (tmp && !(path = ft_strdup(ft_strchr(tmp->content, '=') + 1)))
		return ;
	if (access(path, F_OK) == -1)
		ft_putendl_fd("cd: HOME not found", 2);
	else if (access(path, R_OK) == -1)
		ft_putendl_fd("cd: HOME: Permission Denied", 2);
	else if (chdir(path) != 0)
		ft_putendl_fd("cd: Home not found", 2);
	ft_strdel(&path);
}

void	old_pwd(t_list **env, char *path)
{
	t_list	begin;
	t_list	*tmp;

	begin.next = *env;
	tmp = &begin;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = ft_lstnew(path, ft_strlen(path))))
		return (ft_putendl_fd("malloc error", 2));
	*env = begin.next;
}

void	get_oldpwd(char *buf, t_list **env)
{
	t_list	*tmp;
	char	*path;

	tmp = *env;
	if (!(path = ft_strjoin("OLDPWD=", buf)))
		return (ft_putendl("malloc error"));
	while (tmp && ft_strncmp("OLDPWD=", tmp->content, 7) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		ft_memdel(&tmp->content);
		tmp->content = path;
		tmp->content_size = ft_strlen(path);
	}
	else
	{
		old_pwd(env, path);
		ft_strdel(&path);
	}
	ft_strdel(&buf);
}

void	my_cd(char **av, t_list **o_env)
{
	char	buf[256];
	int		len;

	getcwd(buf, 256);
	if (av[1] && ft_strncmp(av[1], "/", 1) == 0)
		ft_cd(av[1]);
	else if (av[1] && ft_strcmp(av[1], "-") == 0)
		case1(*o_env);
	else if (!av[1] || ft_strcmp(av[1], "~") == 0 || \
				ft_strcmp(av[1], "--") == 0)
		case2(*o_env);
	else if (av[1] && ft_strncmp(av[1], "~", 1) == 0)
		case3(av, *o_env);
	else if (av[2])
		case4(ft_strdup(buf), av);
	else if (av[1])
	{
		len = ft_strlen(buf);
		buf[len] = '/';
		buf[len + 1] = 0;
		case5(ft_strdup(buf), av);
	}
	get_oldpwd(ft_strdup(buf), o_env);
}
