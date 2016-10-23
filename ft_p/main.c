#include "my_printf.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

void	usage(char *s)
{
  ft_printf("Usage: %s <port>\n", s);
  exit(-1);
}

int	create_server(int port)
{
  int			sock;
  struct protoent	*proto;
  struct sockaddr_in	sin;

  proto = getprotobyname("tcp");
  if (!proto)
    return (-1);
  sock = socket(PF_INET, SOCH_STREAM, proto->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
  listen(sock, 42);
  return (sock);
}

int	main(int ac, char **av)
{
  int	port;
  int	sock;
  int	cs;

  if (ac != 2)
    usage(av[0]);
  port = ft_atoi(av[1]);
  sock = create_server(port);
  cs = accept();
  close(sock);
  return (0);
}
