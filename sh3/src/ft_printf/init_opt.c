/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:24:35 by abombard          #+#    #+#             */
/*   Updated: 2015/02/04 19:13:01 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

void    init_opt(t_pf **list)
{
  t_pf          *tmp;

  tmp = *list;
  if (tmp->arg)
    {
		if (ft_strncmp(tmp->arg, "d", 1) == 0 || ft_strncmp(tmp->arg, "hd", 2) == 0 \
			|| ft_strncmp(tmp->arg, "i", 1) == 0)
			tmp->opt = S_INT;
		else if (ft_strncmp(tmp->arg, "o", 1) == 0)
			tmp->opt = US_OCT;
		else if (ft_strncmp(tmp->arg, "u", 1) == 0)
			tmp->opt = US_DECI;
		else if (ft_strncmp(tmp->arg, "x", 1) == 0)
			tmp->opt = US_HEX_MIN;
		else if (ft_strncmp(tmp->arg, "X", 1) == 0)
			tmp->opt = US_HEX_MAJ;
		else if (ft_strncmp(tmp->arg, "s", 1) == 0)
			tmp->opt = STRING;
		else if (ft_strncmp(tmp->arg, "c", 1) == 0)
			tmp->opt = CHAR;
		else if (ft_strncmp(tmp->arg, "p", 1) == 0)
			tmp->opt = PT;
		else
			tmp->string = my_stradd(&tmp->string, tmp->arg, 0);
		ft_strdel(&tmp->arg);
    }
}
