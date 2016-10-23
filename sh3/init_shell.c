/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 14:37:51 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 14:58:15 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		sh1(char ***av, t_list **env, t_sh **g_shref)
{
	int		x;

	x = -1;
	while (++x < 7)
	{
		if (ft_strcmp((*g_shref)[x].str, (*av)[0]) == 0)
		{
			(*g_shref)[x].fun(*av, env);
			return (0);
		}
	}
	return (0);
}

void	del_shref(t_sh **shref)
{
	int	x;

	x = -1;
	while (++x < 7)
		ft_strdel(&(*shref)[x++].str);
	free(*shref);
}

char	**init_arguments(char *cmd)
{
	char	**av;
	char	**tmp;
	int		x;

	av = NULL;
	if (!(av = my_split_whitespace_but(cmd, '"')))
		return (NULL);
	x = -1;
	while (av[++x])
		if (ft_strchr(av[x], '"'))
		{
			if ((tmp = ft_strsplit(av[x], '"')))
			{
				if (!(av = rebuild_tab(&av, &tmp, x)))
				{
					ft_putendl("failed rebuilding av");
					break ;
				}
				free(tmp);
				x = 0;
			}
		}
	return (av);
}

int		if_redirection(char *cmd, char c)
{
  int	x;

  x = 0;
  while (cmd[x])
    {
      if (cmd[x] == c && !betw_char(cmd, x, '"'))
	return (1);
      x++;
    }
  return (0);
}

void	init_shell(char *cmd, t_list **env)
{
	t_sh	*shref;
	char	**av;

	if (if_redirection(cmd, '<') || if_redirection(cmd, '>') \
		|| if_redirection(cmd, '|'))
		return (redirection(cmd, env));
	if (!(av = init_arguments(cmd)))
		return ;
	if (!(shref = init_shref()))
		return ;
	sh1(&av, env, &shref);
	del_stab(&av);
	del_shref(&shref);
}
