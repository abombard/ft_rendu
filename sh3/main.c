/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 17:15:44 by abombard          #+#    #+#             */
/*   Updated: 2015/02/23 17:45:40 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	redirection(char *cmd, t_list **env)
{
	char	**sp;
	char	**sr;

	sp = NULL;
	sr = NULL;
	if ((sp = ft_strsplit(cmd, '|')))
	{
		trim_tab(&sp);
		init_pipe(sp, env);
		del_stab(&sp);
	}
	else if ((sr = split_redirections(cmd)))
	{
		init_redir(sr, env);
		del_stab(&sr);
	}
	else if (cmd && cmd[0] != '<' && cmd[0] != '>')
		init_shell(cmd, env);
}

void	split_cmd(char *line, t_list **env)
{
	char	**cmd;
	char	*tmp;
	int		fd_in;
	int		x;

	if (!(tmp = ft_strdup(line)))
		return ;
	if ((fd_in = errors(&tmp, env)) == 1)
		return ;
	if (!(cmd = ft_strsplit_but(tmp, ';', '"')))
		return (ft_putendl_fd("error", 2));
	ft_strdel(&tmp);
	x = 0;
	while (cmd[x])
	{
		if ((tmp = ft_strtrim(cmd[x++])))
		{
			init_shell(tmp, env);
			ft_strdel(&tmp);
		}
	}
	del_stab(&cmd);
}

void		left(t_lisp **tmp, t_stock *caps)
{
  if (*tmp && (*tmp)->prev)
    {
      *tmp = (*tmp)->prev;
      tputs(caps->left, 1, &puti);
    }
}

void		right(t_lisp **tmp, t_stock *caps)
{
  if (*tmp && (*tmp)->next)
    {
      *tmp = (*tmp)->next;
      tputs(caps->right, 1, &puti);
    }
}

void	arrows(char buf, t_lisp **tmp, t_stock *caps, t_lisp **hist)
{
	if (buf == 68)
		left(tmp, caps);
	else if (buf == 67)
		right(tmp, caps);
	else if (*hist && 
		 ((buf == 65 && (*hist)->prev) || buf == 66))
	  {
	    *tmp = first(*tmp);
	    if ((buf == 65 || (buf == 66 && (*hist)->next)))
	      {
		if (find_elem(*hist, (value)(*tmp)))
		  *hist = buf == 65 ? prev(*hist) : next(*hist);
		lspdel(tmp);
		*tmp = last(lspcpy((*hist)->content.lisp));
	      }
	      else
		lspdel(tmp);
	    tputs(caps->dl, 1, &puti);
	    tputs(caps->cr, 1, &puti);
	    if (*tmp)
	      aff_lisp(first(*tmp));
	  }
	//	ft_printf("\nHere i am: %c\n", (*tmp)->c);
}

void		send_cmd(t_lisp *beg)
{
  char	buf[lisp_len(beg) + 1];
  int	i;
  t_list *env;

  i = 0;
  while (beg)
    {
      buf[i++] = beg->content.c;
      beg = beg->next;
    }
  buf[i] = 0;
  env = get_env(NULL);
  split_cmd(buf, &env);
}

void		input(t_stock *caps, t_lisp **cmd, t_lisp *tmp, t_lisp **hist)
{
  char buf[3];

  ft_bzero(buf, 3);
  read(0, buf, 3);
  if (buf[0] == 27 && buf[1] == 91)
    {
      arrows(buf[2], &tmp, caps, hist);
      *cmd = first(tmp);
    }
  else if (buf[0] == 127 && !buf[1] && tmp)
  {
	tmp = lspdelone(cmd, &tmp);
	tputs(caps->left, 1, &puti);
	tputs(caps->del, 1, &puti);
  }
  else if (buf[0] == 10 && !buf[1])
  {
    if (lisp_len(*hist) > 10)
      del_first(hist);
    lsppush(hist, lspnew((value)(*cmd), LISP));
    *hist = next(*hist);
    send_cmd(*cmd);
    *cmd = NULL;
    tmp = NULL;
    tputs(caps->dl, 1, &puti);
    tputs(caps->cr, 1, &puti);
  }
  else if (ft_isprint(buf[0]))
  {
	write(1, buf, 3);
	if (!(tmp = lspnew((value)buf[0], CHAR)))
	  return ;
	lsppush(cmd, tmp);
  }
  if (buf[0] != 'q')
    input(caps, cmd, tmp, hist);
  *hist = first(*hist);
  //ft_printf("\n%d : %d : %d\n", buf[0], buf[1], buf[2]);
}

int		main(int argc, char **argv, char **environ)
{
	t_list	*env;

	(void)argc;
	(void)argv;
	struct termios oldter;
	struct termios ter;
	t_stock tcaps;

	char *termname;

	termname = getenv("TERM");
	if (tgetent(NULL, termname) < 1)
	  {
	    ft_putendl_fd("Could not access termcap database", 2);
	    return (-1);
	  }

	tcgetattr(0, &oldter);
	ter = oldter;
	ter.c_lflag &= ~(ICANON | ECHO);
	ter.c_cc[VMIN] = 1;
	ter.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &ter);
	if (environ && *environ)
		if (init_var(&env, NULL, environ) == 1)
			return (0);
	init_termcaps(&tcaps);

	t_lisp *hist = NULL;
	t_lisp *cmd = NULL;
	input(&tcaps, &cmd, cmd, &hist);
	lspdel(&hist);
	lspdel(&cmd);
	ft_lstdel(&env, ft_bzero);
	tcsetattr(0, TCSANOW, &oldter);
	return 0;
}
