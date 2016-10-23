#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int main(int ac, char **av)
{
  int fd;

  if (ac > 1)
    {
      if ((fd = open(av[1], O_RDONLY, 0644)) == -1)
	ft_putendl("open error");;
    }
  else 
    fd = 0;
  _fat_cat(fd);
  close(fd);
  return (0);
}
