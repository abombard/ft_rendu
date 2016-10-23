/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 17:15:44 by abombard          #+#    #+#             */
/*   Updated: 2015/03/20 18:10:36 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"
#include <fcntl.h>

int		puti(int c)
{
  if (c)
    {
      ft_putchar(c);
      return (1);
    }
  return (0);
}

int		print_list(t_lisp *tmp, t_stock *info)
{
	int	mem;
	int	x;
	int	c_line;
	int	c_col;

	CLR;
	if (info->maxlen >= info->maxcol)
	  return (-1);
//  ft_printf("col: %d\nline: %d\nmaxlen: %d\n", col, line, tmp->maxlen);
	mem = tmp->rang;
	c_line = 0;
	while (tmp->rang != mem || c_line == 0)
	  {
		c_col = 0;
		while (c_col + info->maxlen <= info->maxcol)
		{
		  tputs(tgoto(info->ret, c_col, c_line), info->fd, &puti);
			if (tmp->select)
			  BOLD_GREEN;
			if (tmp->on)
			  SET_UL;
			tputs(tmp->content, info->fd, &puti);
			if (tmp->on)
			  UNSET_UL;
			x = -1;
			while (++x < info->maxlen - ft_strlen(tmp->content))
			  tputs(" ", info->fd, &puti);
			END_COL;
			tmp = tmp->next;
			if (tmp->rang == mem)
			  break ;
			c_col += info->maxlen;
		}
		if (++c_line > info->maxline)
		  {
		    CLR;
		    info->g_ret = -1;
		    return (-1);
		  }
	  }
	info->g_ret = 0;
	info->lline = c_line - 1;
	info->lcol = c_col;
	return (0);
}

int    init_term()
{
	char	*termname;

	if (!(termname = getenv("TERM")))
		ft_printf("getenv return %s\n", termname);
	if (tgetent(NULL, termname) < 1)
	{
	  ft_putendl_fd("Could not access termcap data base\n", 2);
		return (-1);
	}
	return (0);
}

void	destruct_lisp(t_lisp **tmp, int aff)
{
	t_lisp	*nxt;
	int		cmp;

	cmp = (*tmp)->rang;
	if ((*tmp)->select && aff == 1)
	  ft_printf("%s ", (*tmp)->content);
	*tmp = (*tmp)->next;
	while (1)
	  {
		if ((*tmp)->rang == cmp)
		  break ;
		nxt = (*tmp)->next;
		if ((*tmp)->select && aff == 1)
			ft_printf("%s ", (*tmp)->content);
		free(*tmp);
		*tmp = nxt;
	  }
	free(*tmp);
}

int	get_maxlen(char **av)
{
   int	x;
   int	ret;

   ret = 0;
   x = 0;
   while (av[++x])
   {
       if (ft_strlen(av[x]) > ret)
		   ret = ft_strlen(av[x]);
   }
   return (ret);
}

t_lisp	*init_lisp(char **av)
{
	t_lisp	beg;
	t_lisp	*tmp;
	int		x;

	x = 1;
	tmp = &beg;
	while (av[x])
	  {
		if (!(tmp->next = malloc(sizeof(t_lisp))))
			return (NULL);
		tmp->next->last = tmp;
		tmp = tmp->next;
		tmp->content = av[x];
		tmp->rang = x - 1;
		tmp->select = 0;
		tmp->on = 0;
		x++;
	  }
	tmp->next = beg.next;
	beg.next->last = tmp;
	beg.next->on = 1;
	return (beg.next);
}

int	main(int ac, char **av)
{
	struct termios	oldter;
	struct termios	ter;
	t_lisp		*beg;
	
	if (ac > 1)
	  {
	    if (init_term() == -1)
	      return (-1);
	    tcgetattr(0, &oldter);
	    tcgetattr(0, &ter);
	    ter.c_lflag &= ~(ICANON | ECHO | ISIG);
	    ter.c_cc[VMIN] = 0;
	    ter.c_cc[VTIME] = 0;
	    tcsetattr(0, TCSADRAIN, &ter);
	    
	    if (!(beg = init_lisp(av)))
	      return (-1);
	    int opt = ftw(&beg, get_maxlen(av) + 2, ter, oldter);
	    if (opt != -2)
	      destruct_lisp(&beg, opt);
	    if ((tcsetattr(0, TCSANOW, &oldter) < 0))
	      ft_putstr_fd("Fucked up. Restart your terminal", 2);
	    close (0);
	  }
	ft_putchar('\n');
	return (0);
}
