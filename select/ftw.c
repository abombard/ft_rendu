/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 14:32:29 by abombard          #+#    #+#             */
/*   Updated: 2015/03/25 15:39:54 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"
#include <signal.h>

int	highest_rang(t_lisp *tmp)
{
  int	ret;
  int	mem;

  mem = tmp->rang;
  ret = tmp->rang;
  tmp = tmp->next;
  while (tmp->rang != mem)
    {
      if (tmp->rang > ret)
	ret = tmp->rang;
      tmp = tmp->next;
    }
  return (ret);
}

int	get_rang(t_lisp *tmp)
{
  int	cmp;
  int	blow;
  int	up;
  int	ret;

  ret = 0;
  blow = 0;
  up = 0;
  cmp = tmp->rang;
  tmp = tmp->next;
  while (tmp->rang != cmp)
    {
      if (tmp->rang > cmp)
	up += 1;
      if (tmp->rang < cmp)
	blow += 1;
      tmp = tmp->next;
    }
  if (!blow && !up)
    ret = -2;
  else if (!blow)
    ret = -1;
  else if (!up)
    ret = 1;
  return (ret);
}

int	act(t_stock *info, int opt, t_lisp *tmp)
{
  int	ret;
  int	nbcol;

  nbcol = info->maxcol / info->maxlen;
  ret = 0;
  if (opt == 3) // NEXT LINE
    {
      if (info->line == info->lline
	  || (info->line == info->lline - 1 && info->col > info->lcol))
	info->line = 0;
      else
	info->line += 1;
      ret = info->line == 0 ? info->col / info->maxlen : tmp->rang + nbcol; 
    }
  if (opt == 2) // PREV LINE
    {
      if (info->line == 0)
	{
	  ret = info->col > info->lcol ?
	    highest_rang(tmp) - ((info->lcol / info->maxlen)
				 + (nbcol - (info->col / info->maxlen)))
	    : highest_rang(tmp) - ((info->lcol - info->col) / info->maxlen);
	  info->line = info->col > info->lcol ? info->lline - 1 : info->lline;
	}
      else
	{
	  ret = tmp->rang - nbcol;
	  info->line -= 1;
	}
    }
  tputs(tgoto(info->ret, info->col, info->line), info->fd, &puti);
  return (ret);
}

void	reaff(t_lisp *tmp, t_stock *info)
{
  tmp->on = 0;
  DEL;
  RET;
  if (tmp->select)
    {
      BOLD_GREEN;
      tputs(tmp->content, info->fd, &puti);
      END_COL;
    }
  else
    tputs(tmp->content, info->fd, &puti);
}

void	aff(t_lisp *tmp, t_stock *info)
{
  RET;
  DEL;
  RET;
  SET_UL;
  if (tmp->select)
    {
      tputs(FONT_GREEN, info->fd, &puti);
      BOLD_BLUE;
    }
  tputs(tmp->content, info->fd, &puti);
  UNSET_UL;
  END_COL;
  RET;
}

t_lisp	*right(t_lisp *tmp, t_stock *info)
{
  tmp = tmp->next;
  if (get_rang(tmp->last) == 1 || info->col + 2 * info->maxlen > info->maxcol)
    {
      info->col = 0;
      info->line = get_rang(tmp->last) == 1 ? 0 : info->line + 1;
    }
  else
    info->col += info->maxlen;
  aff(tmp, info);
  return (tmp);
}

t_lisp	*left(t_lisp *tmp, t_stock *info)
{
  int	nbcol;

  tmp = tmp->last;
  if ((nbcol = (info->maxcol / info->maxlen))
      * info->maxlen + info->maxlen > info->maxcol)
    nbcol -= 1;
  if (info->col == 0)
    {
      info->col = info->line == 0 ? info->lcol : nbcol * info->maxlen;
      info->line = info->line == 0 ? info->lline : info->line - 1;
    }
  else
    info->col -= info->maxlen;
  aff(tmp, info);
  return (tmp);
}

t_lisp	*prevline(t_lisp *tmp, t_stock *info)
{
  int	cmp;

  cmp = PREVLINE;
  while (tmp->rang != cmp)
    tmp = tmp->last;
  tmp->on = 1;
  aff(tmp, info);
  return (tmp);
}

t_lisp	*nxtline(t_lisp *tmp, t_stock *info)
{
  int	cmp;

  cmp = NXTLINE;
  while (tmp->rang != cmp)
    tmp = tmp->next;
  tmp->on = 1;
  aff(tmp, info);
  return (tmp);
}

void	ft_select(t_lisp *tmp, t_stock *info)
{
  tmp->select = tmp->select ? 0 : 1;
  DEL;
  RET;
  if (tmp->select)
    BOLD_GREEN;
  if (tmp->rang == tmp->next->rang)
    SET_UL;
  tputs(tmp->content, info->fd, &puti);
  if (tmp->rang == tmp->next->rang)
    UNSET_UL;
  END_COL;
  RET;
}

int	re_init_rang(t_lisp *del, int ret)
{
  if (get_rang(del) != -2)
    {
      while (get_rang(del) != -1)
	del = del->next;
      del->rang = 0;
      while ((del = del->next) && del->rang != 0)
	del->rang = del->last->rang + 1;
      ret = ret == 44 ? ret : 2;
    }
  else
    {
      while (highest_rang(del) != del->rang)
	del = del->next;
      del = del->next;
      del->rang = 0;
      while ((del = del->next) && del->rang != 0)
	del->rang = del->last->rang + 1;
    }
  return (ret);
}

int	exceptions(t_lisp *del)
{
  int	ret;

  ret = 0;
  if (del->rang == del->next->rang)
    ret = -2;
  else if (get_rang(del) != 1)
    {
      if (get_rang(del) != -1)
	ret = 42;
      else
	ret = 44;
    }
  else
    {
      if (get_rang(del) != -1)
	ret = 43;
      else
	ret = -2;
    }
  return (ret);
}

int	del_node(t_lisp **tmp, t_stock *info)
{
	t_lisp	*del;
	int		nbcol;
	int		ret;
	
	nbcol = (info->maxcol / info->maxlen);
	if ((ret = exceptions(*tmp)) != -2)
    {
		del = *tmp;
		(*tmp)->last->next = (*tmp)->next;
		(*tmp)->next->last = (*tmp)->last;
		*tmp = ret == 43 ? (*tmp)->last : (*tmp)->next;
		if (ret == 43)
		{
			if (info->col == 0)
			{
				info->col = nbcol * info->maxlen;
				info->line = info->line - 1;
			}
			info->col -= info->maxlen;
		}
		(*tmp)->on = 1;
		free(del);
		ret = re_init_rang(*tmp, ret);
    }
	return (ret);
}

void	arrows(t_lisp **tmp, t_stock *info, unsigned char *buf)
{
	if ((*tmp)->rang != (*tmp)->next->rang)
    {
		reaff(*tmp, info);
		if (buf[2] == 65)
			*tmp = prevline(*tmp, info);
		else if (buf[2] == 66)
			*tmp = nxtline(*tmp, info);
		else if (buf[2] == 67)
			*tmp = right(*tmp, info);
		else if (buf[2] == 68)
			*tmp = left(*tmp, info);
    }
}

int	ft_read(t_lisp **tmp, unsigned char *buf, t_stock *info)
{
	int		ret;

	ret = 0;
	if (buf[0] == 27)
    {
		if (!buf[2])
			ret = -1;
		else
			arrows(tmp, info, buf);
    }
	else if (buf[0] == 127 && !buf[1])
    {
      ret = del_node(tmp, info);
		if (ret == -2 || ret == 3)
			return (ret);
    }
	else if (buf[0] == 32)
    {
		ft_select(*tmp, info);
		if ((*tmp)->rang != (*tmp)->next->rang)
			*tmp = right(*tmp, info);
    }
	else if (buf[0] == '\n')
		ret = 1;
	return (ret);
}

int	too_small(t_stock *info)
{
	if (info->maxcol > 20 && info->maxline > 5)
	  tputs("I can't work\nin this conditions\n", info->fd, &puti);
	else if (info->maxcol > 5 && info->maxline > 1)
	  tputs("Uff..", info->fd, &puti);
	return (-2);
}

int	redimension(t_stock *info, t_lisp **tmp, t_lisp **beg)
{
  int	ret;

	(*tmp)->on = 0;
	info->line = 0;
	info->col = 0;
	*tmp = *beg;
	(*tmp)->on = 1;
	ret = print_list(*beg, info);
	HOME;
	return (ret);
}

int	handle_ret(t_stock *info, t_lisp **beg)
{
	if (info->g_ret == 2 || info->g_ret == 44
	    || info->g_ret == 43)
    {
		if (info->g_ret == 44)
			*beg = (*beg)->next;
		info->g_ret = print_list(*beg, info);
		RET;
    }
	return (info->g_ret);
}

int	sig_handler(unsigned char *buf)
{
      if (buf[0] == 3 || buf[0] == 4)
	return (-2);
      if (buf[0] == 24)
	  return (42);
      return (0);
}

int	aff_loop(t_lisp **beg, t_lisp *tmp, t_stock *info)
{
	unsigned char	buf[3];
	struct winsize	w;

	ft_bzero(buf, 3);
	while (read(0, buf, 3) >= 0)
    {
      if (sig_handler(buf))
	return (sig_handler(buf));		
		if (ioctl(info->fd, TIOCGWINSZ, &w) != -1
		    && (info->maxline != w.ws_row || info->maxcol != w.ws_col))
		  {
		    info->maxline = w.ws_row;
		    info->maxcol = w.ws_col;
		    info->g_ret = redimension(info, &tmp, beg);
		  }
		if (info->g_ret == -1)
			info->g_ret = too_small(info);
		else
		{
			info->g_ret = ft_read(&tmp, buf, info);
			if (info->g_ret == -1 || info->g_ret == -2 || info->g_ret == 1)
				break ;
			info->g_ret = handle_ret(info, beg);
		}
		ft_bzero(buf, 3);
    }
	return (info->g_ret);
}

int	init_info(t_stock *info)
{
  info->term = getenv("TERM");
  info->home = tgetstr("ho", &info->term);
  info->clr = tgetstr("cl", &info->term);
  info->del = tgetstr("ec", &info->term);
  info->ret = tgetstr("cm", &info->term);
  info->push = tgetstr("cm", &info->term);
  info->pop = tgetstr("rc", &info->term);
  info->set_ul = tgetstr("us", &info->term);
  info->unset_ul = tgetstr("ue", &info->term);
  info->maxline = tgetnum("li");
  info->maxcol = tgetnum("co");
  info->col = 0;
  info->line = 0;
  info->g_ret = 0;
  if (!info->term || !info->home || !info->clr || !info->del || !info->ret
      || !info->set_ul || !info->unset_ul || info->maxline == -1 || info->maxcol == -1)
    return (-1);
  return (1);
}

int	ftw(t_lisp **beg, int maxlen, struct termios ter, struct termios oldter)
{
	t_stock		info;
	int		ret;
	char		*curs_on;
	char		*curs_off;

	if (init_info(&info) == -1)
	  return (-2);
	info.maxlen = maxlen;
	info.fd = open("/dev/tty", O_WRONLY | O_NOCTTY | O_NONBLOCK);
	if (!isatty(info.fd))
    {
		ft_putendl_fd("coudlnt access the terminal data base", 2);
		return (-1);
    }
	(*beg)->on = 1;
	if ((curs_off = tgetstr("vi", &info.term)))
	  tputs(curs_off, info.fd, &puti);
	info.g_ret = print_list(*beg, &info);
	while ((ret = aff_loop(beg, *beg, &info)) == 42)
	  {
	    if ((curs_on = tgetstr("ve", &info.term)))
	      ft_putstr_fd(curs_on, info.fd);
	    ft_putstr_fd(info.clr, info.fd);
	    ioctl(info.fd, TCSBRK, TCIOFF);

	    (void)ter;
	    (void)oldter;
		  ft_putstr_fd(info.clr, info.fd);
		  info.g_ret = print_list(*beg, &info);
		  info.col = 0;
		  info.line = 0;
		  if ((curs_off = tgetstr("vi", &info.term)))
		    ft_putstr_fd(curs_off, info.fd);
	  }
	tputs(info.clr, info.fd, &puti);
	if ((curs_on = tgetstr("ve", &info.term)))
	  tputs(curs_on, info.fd, &puti);
	close(info.fd);
	return (ret);
}
