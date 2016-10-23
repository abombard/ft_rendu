#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 10:05:24 by abombard          #+#    #+#              #
#    Updated: 2015/02/17 12:33:49 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= 	gcc -Wall -Wextra -Werror -O
RM= 	rm -f
SRC=	main.c \
	get_next_line.c \
	outdoor.c \
	swap.c \
	rotate.c \
	rev_rotate.c \
	push.c \
	annexe.c \
	datfun.c \
	ft_swap.c \

OBJ=	$(SRC:.c=.o)
NAME=	push_swap
EXEC=	ft_printf

.PHONY: $(EXEC)

all :	$(EXEC) $(NAME)

$(EXEC):
	@$(MAKE) -C $(EXEC)

%.o: %.c
	@$(GCC) -c $^ -I./includes
	@echo "\033[0;33m$@ was created\033[0m"

$(NAME) :	$(OBJ)
	@$(GCC) -c $(SRC) -I./includes/
	@$(GCC) $(OBJ) -o $(NAME) -L./$(EXEC) -lftprintf -L./$(EXEC)/libft/ -lft

clean :
	@$(MAKE) $@	-C $(EXEC)/
	@$(RM) $(OBJ)

fclean : clean
	@$(MAKE) $@ -C $(EXEC)/
	@$(RM) $(NAME)

re :	fclean	all

here :
	$(RM) $(OBJ) $(NAME)
