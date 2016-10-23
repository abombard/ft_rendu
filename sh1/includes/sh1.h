/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 09:44:40 by abombard          #+#    #+#             */
/*   Updated: 2015/01/05 22:03:30 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include "lisp.h"
# include "tcaps.h"
# include "libft.h"
# include "my_printf.h"
# include "key.h"
# include "magic_tab.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <signal.h>

typedef struct	s_sh
{
	char	*str;
	void	(*fun)(char **, t_list **);
}				t_sh;

void			sign(int sig);
t_list			*get_env(char **environ);
int				init_var(t_list **env, t_sh **g_shref, char **environ);
t_sh			*init_shref(void);
t_list			*get_env(char **environ);
void			delcontent(void *content, size_t n);
void			ex(char **av, t_list **env);
void			set_env(char **av, t_list **env);
void			unset_env(char **av, t_list **env);
void			list_env(char **av, t_list **env);
void			pwd(char **av, t_list **env);
void			my_cd(char **av, t_list **env);
void			env_fun(char **av, t_list **env);
void			free_dat(char **av);
void			case3(char **av, t_list *env);
void			case4(char *path, char **av);
void			case5(char *buf, char **av);

void	key_up(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_down(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_left(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_right(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_del(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_enter(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_begline(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_endline(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_next_word(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_prev_word(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_lineup(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_linedown(t_stock *caps, t_lisp **hist, t_lisp **tmp);
void	key_paste(t_stock *caps, t_lisp **tmp, t_lisp **copy);
int	get_line(t_stock *caps, t_lisp *tmp);
int	maxline(t_stock *caps, t_lisp *tmp);
int	len_check(t_lisp *tmp);
int	len_back(t_lisp *tmp);
void	send_cmd(t_lisp *tmp);

#endif
