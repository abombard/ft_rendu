/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 16:56:55 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:00:28 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	case3(char **av, t_list *env)
{
	t_list	*tmp;
	char	*path;

	tmp = env;
	while (tmp && ft_strncmp(tmp->content, "HOME=", 5) != 0)
		tmp = tmp->next;
	if (tmp && !(path = ft_strjoin(ft_strchr(tmp->content, '=') + 1, \
									av[1] + 1)))
		return ;
	ft_cd(path);
	ft_strdel(&path);
}

void	case4(char *path, char **av)
{
	char	*trig;
	char	*next;
	int		len1;

	if (!(trig = ft_strstr(path, av[1])))
	{
		ft_strdel(&path);
		return (ft_putendl_fd("string not in pwd", 2));
	}
	len1 = ft_strlen(path) - ft_strlen(trig);
	trig = ft_strsub(path, 0, len1);
	next = ft_strsub(path, len1 + ft_strlen(av[1]), len1 - ft_strlen(av[2]));
	ft_strdel(&path);
	path = ft_strjoin(trig, av[2]);
	ft_strdel(&trig);
	trig = ft_strjoin(path, next);
	ft_strdel(&path);
	ft_strdel(&next);
	if ((len1 = chdir(trig)) != 0)
		ft_putstr_fd("No such file or directory: ", 2);
	ft_putendl_fd(trig, len1 != 0 ? 2 : 1);
	ft_strdel(&trig);
}

void	case5(char *buf, char **av)
{
	char	*path;

	path = NULL;
	if (!(path = ft_strjoin(buf, av[1])))
		return (ft_putendl_fd("malloc error", 2));
	ft_cd(path);
	ft_strdel(&path);
	ft_strdel(&buf);
}

void	ft_cd(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (access(path, R_OK) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
		chdir(path);
}
