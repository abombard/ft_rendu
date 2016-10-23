/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 09:44:40 by abombard          #+#    #+#             */
/*   Updated: 2015/02/10 15:08:43 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include "libft.h"
# include "get_next_line.h"
# include "my_printf.h"
# include "lisp.h"
# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct	s_sh
{
	char	*str;
	void	(*fun)(char **, t_list **);
}				t_sh;

typedef struct	s_stock
{
	int	col;
	int	line;
	int	maxline;
	int	maxcol;
	int	lcol;
	int	lline;
	int	maxlen;
	int	fd;
	int	g_ret;
	char	*term;
	char	*home;
	char	*right;
	char	*left;
	char	*up;
	char	*down;
	char	*clr;
	char	*del;
	char	*dl;
	char	*cr;
	char	*ret;
	char	*push;
	char	*pop;
	char	*set_ul;
	char	*unset_ul;
}		t_stock;


void			ft_cd(char *path);
void			access_error(char *path);
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
void			case_root(char *path);
char			**ft_strsplit_but(const char *s, char c, char p);
char			**my_split_whitespace_but(char *str, char p);
char			**rebuild_tab(char ***t1, char ***t2, int trig);
int				betw_char(char *pt, int len, char p);
char			**split_redirections(char *cmd);
void			trim_tab(char ***tab);
void			init_shell(char *cmd, t_list **env);
void			del_stab(char ***tab);
int				readinput(char *trig, int fd);
int				check_doubleinput(char **line, t_list **env);
char			*doubleinput(char **line);
int				errors(char **line, t_list **env);
void			init_pipe(char **sp, t_list **env);
void			init_redir(char **cmd, t_list **env);
void			redirection(char *cmd, t_list **env);
void			init_child_pipe(char **cmd, t_list **env);
void			init_child_redir(char **cmd, t_list **env, int end);
void			split_cmd(char *line, t_list **env);
int			init_termcaps(t_stock *info);
int			puti(int c);
void			ft_lstpush(t_list **alst, t_list *new);

#endif
