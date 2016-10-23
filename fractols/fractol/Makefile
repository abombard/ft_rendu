#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 10:05:24 by abombard          #+#    #+#              #
#    Updated: 2015/01/15 18:45:54 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= 	gcc -Wall -Wextra -Werror -O
RM= 	rm -f
SRC=	main.c \
		init_mlx.c \
		keyboard.c \
		draw_fractol.c \
		buddha.c \

OBJ=	$(SRC:.c=.o)
NAME=	fractol
EXEC=	libft

.PHONY: $(EXEC)

all :	$(EXEC) $(NAME)

$(EXEC):
	@$(MAKE) -C libft/

%.o: %.c
	@$(GCC) -c $^ -I./libft/includes/
	@echo "\033[0;33m$@ was created\033[0m"

$(NAME) :	$(OBJ)
	@$(GCC) -o $(NAME) $(OBJ) -L./libft -lft -L/usr/X11/lib -lmlx -lXext -lX11

clean :
	@$(MAKE) $@	-C libft/
	@$(RM) $(OBJ)

fclean : clean
	@$(MAKE) $@ -C libft/
	@$(RM) $(NAME)

re :	fclean	all

here :
	$(RM) $(OBJ) $(NAME)