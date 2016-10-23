# include "magic_tab.h"

void	magic_tab(fun *tab, int key, fun func)
{
  tab[key] = func;
}

fun	*create_magic_tab()
{
  fun	*beg;

  beg = NULL;
  beg = malloc(sizeof(fun) * 12);
  if (!beg)
    return (NULL);
  magic_tab(beg, MKEY_ENTER, (fun)&key_enter);
  magic_tab(beg, MKEY_UP, (fun)&key_up);
  magic_tab(beg, MKEY_DOWN, (fun)&key_down);
  magic_tab(beg, MKEY_LEFT, (fun)&key_left);
  magic_tab(beg, MKEY_RIGHT, (fun)&key_right);
  magic_tab(beg, MKEY_DEL, (fun)&key_del);
  magic_tab(beg, MKEY_BEGLINE, (fun)&key_begline);
  magic_tab(beg, MKEY_ENDLINE, (fun)&key_endline);
  magic_tab(beg, MKEY_PREVW, (fun)&key_prev_word);
  magic_tab(beg, MKEY_NEXTW, (fun)&key_next_word);
  magic_tab(beg, MKEY_CTRL_UP, (fun)&key_lineup);
  magic_tab(beg, MKEY_CTRL_DOWN, (fun)&key_linedown);
  magic_tab(beg, MKEY_V, (fun)&key_paste);
  return (beg);
}
