#include <sh1.h>

int	puti(int c)
{
	ft_putchar((char)c);
	return (0);
}

int	init_termcaps(t_stock *info)
{
	info->term = getenv("TERM");
	info->home = tgetstr("ho", &info->term);
	info->clr = tgetstr("cl", &info->term);
	info->left = tgetstr("le", &info->term);
	info->right = tgetstr("nd", &info->term);
	info->up = tgetstr("up", &info->term);
	info->down = tgetstr("do", &info->term);
	info->ts = tgetstr("ts", &info->term);
	info->del = tgetstr("dc", &info->term);
	info->cd = tgetstr("cd", &info->term);
	info->dl = tgetstr("dl", &info->term);
	info->del_line = tgetstr("*5", &info->term);
	info->cr = tgetstr("cr", &info->term);
	info->ret = tgetstr("cm", &info->term);
	info->push = tgetstr("sc", &info->term);
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

