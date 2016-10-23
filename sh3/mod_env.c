/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 19:13:52 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 21:08:52 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	do_it(char **av, t_list **o_env)
{
	t_list	begin;
	t_list	*prev;
	t_list	*next;
	char	*path;

	if (!(path = ft_strjoin(av[1], "=")))
		return (ft_putendl_fd("malloc error", 2));
	begin.next = *o_env;
	prev = &begin;
	while (prev->next && ft_strncmp(path, prev->next->content, \
									ft_strlen(path)) != 0)
		prev = prev->next;
	if (!prev || !prev->next)
	{
		ft_putstr_fd("No match found for : ", 2);
		ft_putendl_fd(av[1], 2);
		return (ft_strdel(&path));
	}
	next = prev->next->next;
	ft_lstdelone(&prev->next, &delcontent);
	prev->next = next;
	ft_strdel(&path);
	*o_env = begin.next;
}

void	unset_env(char **av, t_list **o_env)
{
	if (!av[1] || av[2])
		return (ft_putendl_fd("Usage : unsetenv [Var name | all]", 2));
	if (ft_strcmp(av[1], "all") == 0)
		return (ft_lstdel(o_env, &delcontent));
	do_it(av, o_env);
}

void	add_env(t_list **o_env, char *new_content)
{
	t_list	*tmp;

	if (!*o_env)
	{
		if (!(tmp = ft_lstnew(new_content, ft_strlen(new_content))))
			return (ft_putendl_fd("failed creating env", 2));
		*o_env = tmp;
		return (ft_putendl("Environment created"));
	}
	tmp = *o_env;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = ft_lstnew(new_content, ft_strlen(new_content))))
		return (ft_putendl("malloc error"));
}

void	set_env(char **av, t_list **o_env)
{
	t_list	*tmp;
	char	*path;
	char	*new_content;

	if (!av[1] || !av[2] || av[3])
		return (ft_putendl_fd("Usage : setenv [variable] [value]", 2));
	tmp = *o_env;
	if (!(path = ft_strjoin(av[1], "=")))
		return (ft_putendl_fd("malloc error", 2));
	if (!(new_content = ft_strjoin(path, av[2])))
		return (ft_putendl_fd("malloc error", 2));
	while (tmp)
	{
		if (ft_strncmp(tmp->content, path, ft_strlen(path)) == 0)
		{
			ft_memdel(&tmp->content);
			tmp->content = new_content;
			return (ft_strdel(&path));
		}
		tmp = tmp->next;
	}
	add_env(o_env, new_content);
	ft_strdel(&path);
	ft_strdel(&new_content);
}

void	list_env(char **av, t_list **env)
{
	t_list	*tmp;

	(void)av;
	tmp = *env;
	if (!tmp)
		return (ft_putendl_fd("No environment found", 2));
	while (tmp)
	{
		ft_putendl_fd(tmp->content, 2);
		tmp = tmp->next;
	}
}
