#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 10:05:24 by abombard          #+#    #+#              #
#    Updated: 2015/03/25 14:08:31 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= 	gcc -Wall -Wextra -Werror -O
RM= 	rm -f
SRC=	main.c \
		ftw.c \

OBJ=	$(SRC:.c=.o)
NAME=	ft_select
EXEC=	src/ft_printf

.PHONY: $(EXEC)

all :	$(EXEC) $(NAME)

$(EXEC):
	@$(MAKE) -C $(EXEC)
	@echo "\033[0;33m$@ was created\033[0m"

%.o: %.c
	@$(GCC) -c $^ -I./includes/

$(NAME) :	$(OBJ)
	@gcc $(OBJ) -o $(NAME) -L./src/ft_printf/ -lftprintf -L./src/ft_printf/libft -lft -lncurses
	@echo "\033[0;33m$@ was created\033[0m"

clean :
	@$(MAKE) $@	-C $(EXEC)
	@$(RM) $(OBJ)
	@echo "\033[0;33m$@ was deleted\033[0m"

fclean : clean
	@$(MAKE) $@	-C $(EXEC)
	@$(RM) $(NAME)

re :	fclean	all

here :
	$(RM) $(OBJ) $(NAME)
