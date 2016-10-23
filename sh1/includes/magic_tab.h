#ifndef MAGIC_TAB_H
# define MAGIC_TAB_H

# include "sh1.h"

typedef union
{
  void	(*fun)(t_stock *caps, t_lisp **hist, t_lisp **tmp);
}	fun;

fun	*create_magic_tab();
void	magic_tab(fun *beg, int key, fun fun);

#endif
