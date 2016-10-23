/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 17:52:24 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 18:00:57 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

t_sh	*init_shref(void)
{
	t_sh	*shref;

	if (!(shref = (t_sh*)malloc(sizeof(*shref) * 7)))
		return (NULL);
	shref[0].str = ft_strdup("exit");
	shref[0].fun = &ex;
	shref[1].str = ft_strdup("pwd");
	shref[1].fun = &pwd;
	shref[2].str = ft_strdup("cd");
	shref[2].fun = &my_cd;
	shref[3].str = ft_strdup("setenv");
	shref[3].fun = &set_env;
	shref[4].str = ft_strdup("unsetenv");
	shref[4].fun = &unset_env;
	shref[5].str = ft_strdup("env");
	shref[5].fun = &list_env;
	shref[6].str = NULL;
	shref[6].fun = &env_fun;
	return (shref);
}

t_list  *get_env(char **environ)
{
  static t_list   *env = NULL;
  t_list  *tmp;
  int             x;

  if (env == NULL)
    {
      x = 0;
      if (!(env = ft_lstnew(environ[x], ft_strlen(environ[x]) + 1)))
	return (NULL);
      tmp = env;
      while (environ[++x])
	{
	  if ((tmp->next = ft_lstnew(environ[x], ft_strlen(environ[x]))))
	    tmp = tmp->next;
	}
    }
  return (env);
}

int             init_var(t_list **env, t_sh **g_shref, char **environ)
{
  if (environ && !(*env = get_env(environ)))
    {
      ft_putendl("Error: No environment");
      return (1);
    }
  if (g_shref && !(*g_shref = init_shref()))
    return (1);
  return (0);
}



/*
t_list	*get_env(char **environ)
{
	t_list	*env;
	t_list	*tmp;
	int		x;

	x = 0;
	if (!(env = ft_lstnew(environ[x], ft_strlen(environ[x]) + 1)))
		return (NULL);
	tmp = env;
	while (environ[++x])
	{
		if ((tmp->next = ft_lstnew(environ[x], ft_strlen(environ[x]))))
			tmp = tmp->next;
	}
	return (env);
}

int		init_var(t_list **env, t_sh **g_shref, char **environ)
{
	if (!(*env = get_env(environ)))
	{
		ft_putendl("Error: No environment");
		return (1);
	}
	if (!(*g_shref = init_shref()))
		return (1);
	return (0);
}
*/
