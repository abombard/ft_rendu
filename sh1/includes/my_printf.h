/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 18:15:14 by abombard          #+#    #+#             */
/*   Updated: 2015/02/04 21:45:54 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PRINTF_H
# define MY_PRINTF_H

# define PRINTF_BUFSIZE 256

# define CHAR 1
# define STRING 2
# define S_INT 3
# define US_OCT 4
# define US_DECI 5
# define US_HEX_MAJ 6
# define US_HEX_MIN 7
# define PT 8

# include "libft.h"
# include <stdarg.h>

typedef struct	s_pf
{
	char	*string;
	char	*arg;
	int		opt;
	int		field;
	int		precision;
	int		diez;
	int		zero;
	int		moins;
	int		plus;
	int		space;
	int		hh;
	int		h;
	int		ll;
	int		l;
	int		j;
	int		z;
	struct s_pf	*next;
}				t_pf;

typedef struct	s_pfun
{
	int		opt;
	char	*(*fun)(va_list ap, t_pf *node);
}		t_pfun;

int		ft_printf(const char *fmt, ...);
t_pf	*init_args(char *fmt);
void	init_flags(t_pf **list);
void	init_opt(t_pf **list);
t_pfun	*init_fun(void);
void	del_pf(t_pf **list);
int	outdoor(void);
t_pf	*init_list(char *fmt);
char    *get_nbr_hex(unsigned long long nb);
char    *get_hex(unsigned long nb);
char    *get_nbr_oct(unsigned long nb);
char    *my_strcapitalize(char *str);
char	*field_width(char *t, t_pf *node);
char	*precision(char *t, t_pf *node, int opt);
char	*flag(t_pf *node, char **t, int opt);
char	*case_c(va_list ap, t_pf *node);
char	*case_s(va_list ap, t_pf *node);
char	*case_nbr(va_list ap, t_pf *node);
char	*case_p(va_list ap, t_pf *node);
char	*case_o(va_list ap, t_pf *node);
char	*case_u(va_list ap, t_pf *node);
char	*case_x(va_list ap, t_pf *node);
char	*case_X(va_list ap, t_pf *node);

#endif
