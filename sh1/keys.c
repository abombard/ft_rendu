#include "sh1.h"
# include "key.h"

int	get_key(char *buf)
{
  ft_bzero(buf, 6);
  return (read(0, buf, 6) ? 1 : 0);
}

int	key_is(char *buf)
{
  if (buf[0] == 27 && buf[1] == 91)
    {
      if (buf[2] == 49)
	{
	  if (buf[5] == 65)
	    return (MKEY_CTRL_UP);
	  else if (buf[5] == 66)
	    return (MKEY_CTRL_DOWN);
	  else if (buf[5] == 67)
	    return (MKEY_CTRL_RIGHT);
	  else if (buf[5] == 68)
	    return (MKEY_CTRL_LEFT);    
	}
      else if (buf[2] == 68)
	return (MKEY_LEFT);
      else if (buf[2] == 67)
	return (MKEY_RIGHT);
      else if (buf[2] == 65)
	return (MKEY_UP);
      else if (buf[2] == 66)
	return (MKEY_DOWN);
    }
  else if (buf[0] == 127 && !buf[1])
    return (MKEY_DEL);
  else if (buf[0] == 10 && !buf[1])
    return (MKEY_ENTER);
  else if (buf[0] == 1 && !buf[1])
    return (MKEY_BEGLINE);
  else if (buf[0] == 5 && !buf[1])
    return (MKEY_ENDLINE);
  else if (buf[0] == 23 && !buf[1])
    return (MKEY_PREVW);
  else if (buf[0] == 24 && !buf[1])
    return (MKEY_NEXTW);
  else if (buf[0] == 6 && !buf[1])
    return (MKEY_F);
  else if (buf[0] == 22 && !buf[1])
    return (MKEY_V);
  return (16);
}
