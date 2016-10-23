#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 10:05:24 by abombard          #+#    #+#              #
#    Updated: 2015/01/05 13:58:39 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= 	gcc -Wall -Wextra -Werror
RM= 	rm -f
SRC=	main.c \
		init_mlx.c \
		keyboard.c \
		draw_fractol.c \
		buddha.c \

OBJ=	$(SRC:.c=.o)
NAME=	fractol
EXEC=	libft
EXEC2=	minilibx_macos

.PHONY: $(EXEC) $(EXEC2)

all :	$(EXEC) $(EXEC2) $(NAME)

$(EXEC):
	@$(MAKE) -C libft/

$(EXEC2):
	@$(MAKE) -C minilibx_macos/

%.o: %.c
	@$(GCC) -c $^ -I./libft/includes/
	@echo "\033[0;33m$@ was created\033[0m"

$(NAME) :	$(OBJ)
	@$(GCC) -o $(NAME) $(OBJ) -L./libft -lft -L./minilibx_macos -lmlx -framework OpenGL -framework appKit -I./minilibx_macos/

clean :
	@$(MAKE) $@	-C libft/
	@$(MAKE) $@	-C minilibx_macos/
	@$(RM) $(OBJ)

fclean : clean
	@$(MAKE) $@ -C libft/
	@$(MAKE) $@	-C minilibx_macos/
	@$(RM) $(NAME)

re :	fclean	all
