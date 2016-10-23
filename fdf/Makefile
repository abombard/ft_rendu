#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:15:17 by abombard          #+#    #+#              #
#    Updated: 2014/12/10 19:39:23 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= gcc -Wall -Wextra -Werror

RM= rm -f

SRC=	main.c \
		init_mlx.c \
		draw_map.c \
		rot.c \
		aff_type.c \
		aff_map.c \
		get_next_line/get_next_line.c \
		

OBJ=	$(SRC:.c=.o)

NAME=	fdf

EXEC=	libft

all :	$(EXEC) $(NAME)

$(EXEC) :
	@(cd libft && $(MAKE))	

$(NAME) :
	@$(GCC) -o $(NAME) $(SRC) -L./libft -lft -I./libft/includes \
	 -I./get_next_line -L/usr/X11/lib -lmlx -lXext -lX11 -lm

clean :
	@(cd libft && $(MAKE) $@)	
	@$(RM) $(OBJ)

fclean :	clean
	@(cd libft && $(MAKE) $@)	
	@$(RM) $(NAME)

re :	fclean	all

.PHONY: $(EXEC)
