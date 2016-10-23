/*
** my_strcapitalize.c for  in /home/bombar_a/rendu/Piscine_C_J06/ex_09
** 
** Made by arthur bombarde
** Login   <bombar_a@epitech.net>
** 
** Started on  Mon Oct  6 17:27:01 2014 arthur bombarde
** Last update Wed Jan 21 00:32:02 2015 arthur bombarde
*/

char	*my_strcapitalize(char *str)
{
  int	x;

  if (str[0] >= 'a' && str[0] <= 'z')
    {
      str[0] = str[0] - 32;
    }
  x = 1;
  while (str[x])
    {
      if (str[x] >= '0' && str[x] <= '9')
	{
	  x = x + 1;
	} 
      if ((str[x - 1] == ' ' || str[x - 1] == '-' || str[x - 1] == '+') &&
	  (str[x] >= 'a' && str[x] <= 'z'))
	{
	  str[x] = str[x] - 32;
	}
      x = x + 1;
    }
  return (str);
}
