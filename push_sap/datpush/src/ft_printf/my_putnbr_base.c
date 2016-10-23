/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 15:44:00 by abombard          #+#    #+#             */
/*   Updated: 2015/02/05 15:47:15 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	my_putnbr_base(unsigned long nbr, char *base)
{
  return (base[nbr % ft_strlen(base)]);
}

char	*get_nbr_hex(unsigned long long nbr)
{
  char	*base;
  char	*s;
  char	tmp[14];
  int	x;

  base = "0123456789abcdef";
  x = 13;
  tmp[x--] = 0;
  while (nbr > 0)
    {
      tmp[x--] = my_putnbr_base(nbr, base);
      nbr /= ft_strlen(base);
    }
  s = ft_strdup(tmp + x + 1);
  return (s);
}

char	*get_nbr_oct(unsigned long nbr)
{
  char	*base;
  char	*s;
  char	tmp[36];
  int	x;

  if (nbr == 0)
    return (ft_strdup("0"));
  base = "01234567";
  x = 35;
  tmp[x--] = 0;
  while (nbr > 0)
    {
      tmp[x--] = my_putnbr_base(nbr, base);
      nbr /= ft_strlen(base);
    }
  s = ft_strdup(tmp + x + 1);
  return (s);
}

char	*get_hex(unsigned long long nbr)
{
  char	*base;
  char	*s;
  char	tmp[36];
  int	x;

  if (nbr == 0)
    return (ft_strdup("0"));
  base = "0123456789abcdef";
  x = 35;
  tmp[x--] = 0;
  while (nbr > 0)
    {
      tmp[x--] = my_putnbr_base(nbr, base);
      nbr /= ft_strlen(base);
    }
  s = ft_strdup(tmp + x + 1);
  return (s);
}
