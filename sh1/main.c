/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 17:15:44 by abombard          #+#    #+#             */
/*   Updated: 2015/05/11 15:54:08 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	sh1(char *line, t_list **env)
{
	int		x;
	char	**av;
	t_sh	*g_shref;

	g_shref = init_shref();
	if (!g_shref)
	  return ;
	av = NULL;
	x = -1;
	if (!(av = my_split_whitespace(line)))
		return (ft_putendl("malloc error"));
	while (++x < 7)
	{
		if (ft_strcmp((g_shref)[x].str, av[0]) == 0)
		{
			(g_shref)[x].fun(av, env);
			free_dat(av);
			return ;
		}
	}
	x = -1;
	while (++x < 7)
		ft_strdel(&(g_shref)[x++].str);
	free(g_shref);
	free_dat(av);
}

void	send_cmd(t_lisp *beg)
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
  sh1(ft_strtrim(buf), &env);
}

void	insert_char(t_stock *caps, t_lisp *tmp)
{
  int len;
  int totlen;
  int cmp;
  int x;
  int i;

  len = lsplen_for(tmp) - 1;
  totlen = lisp_len(tmp);
  aff_lisp(tmp->next);
  cmp = caps->maxcol - 5;
  while (len--)
    {
      totlen--;
      x = 0;
      while (x * caps->maxcol < totlen)
	{
	  if (totlen == (x * caps->maxcol) + cmp)
	    {
	      tputs(caps->up, 2, &puti);
	      i = caps->maxcol;
	      while (i--)
		tputs(caps->right, 1, &puti);
	    }
	  x++;
	}
      if (totlen != (x * caps->maxcol) + cmp)
	tputs(caps->left, 1, &puti);
    }
}

void	new_char(char *buf, t_lisp **tmp, t_stock *caps)
{
  t_lisp	*new;

  new = lspnew((t_value)buf[0], CHAR, NULL);
  if (!new)
    return ;
  write(1, buf, 3);
  if (!*tmp || (!(*tmp)->next && !(*tmp)->key))
      *tmp = lsppush(tmp, new);
  else
    {
      if (*tmp && !(*tmp)->key)
	*tmp = insert_elem(tmp, new);
      else
	lspadd(tmp, new);
      insert_char(caps, *tmp);
    }
}

void	key_begline(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int	len = lsplen_back(*tmp);

  while (len--)
    {
      key_left(caps, hist, tmp);
    }
}

void	key_endline(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int	len = lsplen_for(*tmp);

  while (len--)
    {
      key_right(caps, hist, tmp);
    }
}

void	key_prev_word(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  if (*tmp)
    {
      while ((*tmp)->prev && (*tmp)->content.c == ' ' && (*tmp)->i > -1)
	key_left(caps, hist, tmp);
      while ((*tmp)->prev && (*tmp)->content.c != ' ' && (*tmp)->i > -1)
	key_left(caps, hist, tmp);
      if (!(*tmp)->prev)
	key_left(caps, hist, tmp);
    }
}

void	key_next_word(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  if (*tmp)
    {
      while ((*tmp)->next && (*tmp)->content.c == ' ')
	key_right(caps, hist, tmp);
      while ((*tmp)->next && (*tmp)->content.c != ' ')
	key_right(caps, hist, tmp);
    }
}

void	key_lineup(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int		i;
  int		len;
  int		cmp;

  (void)hist;
  if (!*tmp)
    return ;
  len = len_back(*tmp);
  cmp = len == -1 ? caps->maxcol - 4 : caps->maxcol - 1;
  len = len == -1 ? lsplen_back(*tmp) : len;
  i = 0;
  if (len > cmp)
    while (i++ < caps->maxcol)
      key_left(caps, hist, tmp);
}

void	key_linedown(t_stock *caps, t_lisp **hist, t_lisp **tmp)
{
  int       line;
  int	    mline;
  int	    i;

  if (!*tmp)
    return ;
  (void)hist;
  line = get_line(caps, *tmp);
  mline = get_line(caps, last(*tmp));
  i = 0;
  if (line < mline)
    while (i++ < caps->maxcol)
      key_right(caps, hist, tmp);
}

void	reaff(t_stock *caps, t_lisp *tmp)
{
  int	ml;

  if (caps->g_ret == 1)
    tputs(caps->push, 1, &puti);
  tputs(caps->cr, 0, &puti);
  tputs(caps->cd, 0, &puti);
  ft_printf("$> ");
  if (tmp)
    aff_lisp(first(tmp));
  if (caps->g_ret == 1)
    tputs(caps->pop, 1, &puti);
  ml = get_line(caps, last(tmp));
  if (ml > caps->line)
    tputs(caps->up, 0, &puti);
  caps->line = ml;
}

void	key_paste(t_stock *caps, t_lisp **tmp, t_lisp **copy)
{
  t_lisp *t;

  if (*copy)
    {
      if (*tmp)
	clear_keys(first(*tmp)->next);
      if (!*tmp)
	{
	  lsppush(tmp, lspcpy(*copy));
	  (*tmp)->key = ft_strdup("42");
	}
      else if ((*tmp)->key)
	{
	  ft_strdel(&(*tmp)->key);
	  t = lspcpy(*copy);
	  t->key = ft_strdup("42");
	  lsppush(&t, first(*tmp));
	  *tmp = first(t);
	}
      else
	insert_elem(tmp, lspcpy(*copy));
      reaff(caps, *tmp);
    }
}

# define NORMAL 0
# define COPY 1
# define COPY_RIGHT 2
# define COPY_LEFT 3
# define DONE 4

# define HL 1

# define LEFT 1
# define RIGHT 2

void	reaff_char_bfor(t_stock *caps, char c, int mov, int opt)
{
  if (!c)
    return ;
  if (mov == LEFT)
    tputs(caps->left, 0, &puti);
  else if (mov == RIGHT)
    tputs(caps->right, 0, &puti);
  if (opt == 1)
    tputs(caps->set_ul, 0, &puti);
  ft_putchar(c);
  if (opt == 1)
    tputs(caps->unset_ul, 0, &puti);  
}

void	reaff_char_after(t_stock *caps, char c, int mov, int opt)
{
  if (!c)
    return ;
  if (opt == 1)
    tputs(caps->set_ul, 0, &puti);
  ft_putchar(c);
  if (opt == 1)
    tputs(caps->unset_ul, 0, &puti);
  if (mov == LEFT)
    tputs(caps->left, 0, &puti);
  else if (mov == RIGHT)
    tputs(caps->right, 0, &puti);
}

void	del_copy_right(t_stock *caps, t_lisp **tmp, t_lisp **copy, int *inf)
{
  t_lisp *yolo;

  yolo = last(*copy);
  clear_keys(first(*tmp));
  reaff_char_bfor(caps, (*tmp)->content.c, LEFT, !(*copy) ? HL : 0);
  key_left(caps, NULL, tmp);
  if (yolo)
    lspdelone(copy, &yolo);
  if (!*copy)
    inf[0] = COPY;
}

void	add_copy_right(t_stock *caps, t_lisp **tmp, t_lisp **copy)
{
  key_right(caps, NULL, tmp);
  if ((*tmp)->next || (!(*tmp)->key && *copy))
    {
      if (!(*tmp)->next && !(*tmp)->key)
	(*tmp)->key = ft_strdup("42");
      lsppush(copy, lspnew((*tmp)->content, CHAR, NULL));
      reaff_char_bfor(caps, (*tmp)->content.c, LEFT, HL);
    }
}

void	del_copy_left(t_stock *caps, t_lisp **tmp, t_lisp **copy, int *inf)
{
  t_lisp	*yolo;

  key_right(caps, NULL, tmp);
  yolo = *copy;
  if ((*copy))
    *copy = lspdelone(copy, &yolo);
  if (!*copy)
    inf[0] = COPY;
  reaff_char_bfor(caps, (*tmp)->content.c, LEFT, !(*copy) && !(*tmp)->prev ? HL : 0);
  if (!*copy && !(*tmp)->prev)
    lspadd(copy, lspnew((*tmp)->content, CHAR, NULL));
}

void	add_copy_left(t_stock *caps, t_lisp **tmp, t_lisp **copy)
{
  char		c;

  key_left(caps, NULL, tmp);
  if ((!(*tmp)->key && (*tmp)->next))
    c = (*tmp)->next->content.c;
  else if (*copy && (*tmp)->key && (*tmp)->key[0] == '4' && ((*tmp)->key[0] = '2'))
    c = (*tmp)->content.c;
  else
    return ;
  lspadd(copy, lspnew((t_value)c, CHAR, NULL));
  reaff_char_after(caps, c, LEFT, HL);
}

void	copy_mode(t_stock *caps, t_lisp **tmp, t_lisp **copy, int *inf)
{
  if (!tmp || !*tmp)
    return ;
  if (inf[0] == COPY && (inf[1] == MKEY_RIGHT || inf[1] == MKEY_LEFT))
    {
      inf[0] = inf[1] == MKEY_RIGHT ? COPY_RIGHT : COPY_LEFT;
      if (inf[1] == MKEY_LEFT)
	{
	  lspdel(copy);
	  if ((*tmp)->next && !(*tmp)->next->next)
	    lspadd(copy, lspnew((*tmp)->next->content, CHAR, NULL));
	}
    }
  if (inf[0] == COPY_RIGHT)
    {
      if (inf[1] == MKEY_LEFT)
	del_copy_right(caps, tmp, copy, inf);
      else if (inf[1] == MKEY_RIGHT)
	add_copy_right(caps, tmp, copy);
    }
  else if (inf[0] == COPY_LEFT)
    {
      if (inf[1] == MKEY_RIGHT)
	del_copy_left(caps, tmp, copy, inf);
      else if (inf[1] == MKEY_LEFT)
	add_copy_left(caps, tmp, copy);
    }
  //ft_printf("|"); if (copy) aff_lisp(first(copy)); ft_printf("|");

}

void	input(t_stock *caps)
{
  char		buf[6];
  t_lisp	*hist;
  t_lisp	*tmp;
  t_lisp	*copy;
  fun		*tab;
  int		inf[2];

  caps->g_ret = 1;
  inf[0] = 0;
  hist = NULL;
  tmp = NULL;
  copy = NULL;
  caps->line = 1;
  tab = create_magic_tab();
  if (!tab)
    return ;
  ft_printf("$> ");
  while (1)
    {
      get_key(buf);
      //ft_printf("\n%d : %d : %d : %d : %d : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
      if (buf[0] == 'q')
	break ;
      //continue ;
      inf[1] = key_is(buf);
      if (inf[0] == NORMAL)
	{
	  if (inf[1] < 12)
	    tab[inf[1]].fun(caps, &hist, &tmp);
	  else if (inf[1] == 12)
	    tab[inf[1]].fun(caps, &tmp, &copy);
	  else if (inf[1] == MKEY_F)
	    {
	      lspdel(&copy);
	      inf[0] = COPY;
	    }
	  else if (ft_isprint(buf[0]) && !buf[1])
	    new_char(buf, &tmp, caps);
	}
      else if (inf[1] == MKEY_F)
	{
	  inf[0] = NORMAL;
	  if (tmp)
	    reaff(caps, tmp);
	}
      else if (inf[1] == MKEY_V)
	{
	  inf[0] = NORMAL;
	  t_lisp *beg;
	  t_lisp *t;
	  beg = first(tmp);
	  t = beg;
	  while (t && !lspcmp(t, copy))
	    t = t->next;
	  int len = lisp_len(copy);
	  while (len-- && beg && t)
	    {
	      t_lisp *mem = t->next;
	      lspdelone(&beg, &t);
	      t = mem;
	    }
	  caps->g_ret = 0;
	  tmp = beg ? last(beg) : NULL;
	  reaff(caps, tmp);
	  caps->g_ret = 1;
	}
      else
	copy_mode(caps, &tmp, &copy, inf);
    }
  lspdel(&copy);
  lspdel(&hist);
  free(tab);
}

int	init_raw_mode(struct termios *oldter)
{
  struct termios ter;
  char *termname;

  termname = getenv("TERM");
  if (tgetent(NULL, termname) < 1)
    {
      ft_putendl_fd("Could not access termcap database", 2);
      return (0);
    }
  tcgetattr(0, &ter);
  *oldter = ter;
  ter.c_lflag &= ~(ICANON | ECHO);
  ter.c_cc[VMIN] = 1;
  ter.c_cc[VTIME] = 0;
  tcsetattr(0, TCSADRAIN, &ter);  
  return (1);
}

int	putback_normal_mode(struct termios ter)
{
  return (tcsetattr(0, TCSADRAIN, &ter));
}

int	main(int argc, char **argv, char **environ)
{
  t_list	*env;
  t_stock	tcaps;
  struct termios oldter;

  (void)argc;
  (void)argv;
  if (environ && *environ && init_var(&env, NULL, environ) == 1)
      return (0); 
  if (!init_raw_mode(&oldter))
     return (-1);
  init_termcaps(&tcaps);
  input(&tcaps);
  ft_lstdel(&env, ft_bzero);
  putback_normal_mode(oldter);
  return (0);
}
/*

int		main(int argc, char **argv, char **environ)
{
	char	*line;
	int		inf[1];
	t_list	*env;
	t_sh	*g_shref;

	(void)argc;
	(void)argv;
	if (init_var(&env, &g_shref, environ) == 1)
		return (0);
	while (1)
	{
		inf[1] = 0;
		signal(SIGINT, &sign);
		ft_putstr("$> ");
		if (get_next_line(0, &line) > 0)
		{
			while (line[inf[1]] && ft_isspace(line[inf[1]]) == 0)
				inf[1]++;
			if (line[inf[1]])
				sh1(line, &env, &g_shref);
			ft_strdel(&line);
		}
	}
	return (0);
}
*/
