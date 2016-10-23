/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 18:57:52 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 17:51:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void		free_dat(char **tab)
{
	free(tab[0]);
	free(tab);
	tab = NULL;
}

void		sign(int sig)
{
	(void)sig;
}

void		pwd(char **av, t_list **o_env)
{
	char	buf[256];
	char	*ret;

	(void)av;
	(void)o_env;
	ret = NULL;
	getcwd(buf, 256);
	ret = ft_strdup(buf);
	ft_putendl(ret);
	ft_strdel(&ret);
}

void		delcontent(void *content, size_t n)
{
	(void)n;
	ft_strdel((char**)&content);
}

void		ex(char **av, t_list **o_env)
{
	int		ret;

	ret = 0;
	if (av[1])
		ret = ft_atoi(av[1]);
	free_dat(av);
	ft_lstdel(o_env, &delcontent);
	exit (ret);
}
