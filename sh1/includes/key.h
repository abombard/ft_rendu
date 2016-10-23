#ifndef KEY_H
# define KEY_H

# include "sh1.h"

# define MKEY_ENTER 0
# define MKEY_UP 1
# define MKEY_DOWN 2
# define MKEY_LEFT 3
# define MKEY_RIGHT 4
# define MKEY_DEL 5
# define MKEY_BEGLINE 6
# define MKEY_ENDLINE 7
# define MKEY_PREVW 8
# define MKEY_NEXTW 9
# define MKEY_CTRL_UP 10
# define MKEY_CTRL_DOWN 11
# define MKEY_V 12
# define MKEY_F 13
# define MKEY_CTRL_RIGHT 14
# define MKEY_CTRL_LEFT 15

int     get_key(char *buf);
int	key_is(char *buf);

#endif
