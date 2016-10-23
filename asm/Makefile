#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/19 17:50:57 by abombard          #+#    #+#              #
#    Updated: 2015/02/19 19:35:14 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=	test
NASM=	nasm -f elf64
LD=		ld
RM=		rm -f
SRC=	ft_bzero.s \
		ft_strcat.s \
		ft_isdigit.s \
		ft_isalpha.s \
		ft_isalnum.s \
		ft_isascii.s \
		ft_isprint.s \
		ft_toupper.s \
		ft_tolower.s \
		ft_strlen.s \
		ft_puts.s \
		ft_memset.s \
		ft_memcpy.s \
		ft_strdup.s \
		ft_cat.s \
		ft_strlcat.s \
		puts_err.s \
		ret.s \

OBJ=	$(SRC:.s=.o)

all: $(OBJ)
	$(MAKE) -C libft

%.o: %.s
	@$(NASM) $^
comp:
	@gcc -c main.c -L libft -lft -I libft/includes
	@gcc main.o $(OBJ) -L libft -lft -I libft/includes -o $(NAME)
clean:
	@$(RM) $(OBJ)
	@$(RM) main.o
fclean: clean
	@$(RM) $(NAME)

re: fclean all
