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

GCC=gcc -Wall -Wextra -Werror -O
RM=rm -f
SRC=	main.c \
	init_var.c \
	opt.c \
	exec.c \
	mod_env.c \
	my_cd.c \
	my_cd2.c \
	get_next_line.c \
	init_termcaps.c \
	lisp.c \
	keys.c \
	magic_tab.c \
	key_fun.c \

OBJ=$(SRC:.c=.o)
NAME=ft_minishell3
EXEC_PRINTF= ./src/ft_printf
EXEC_LFT= ./src/libft
EXEC=exec


.PHONY: $(EXEC)

all :	$(NAME)

$(EXEC):
	@$(MAKE) -C $(EXEC_LFT)
	@$(MAKE) -C $(EXEC_PRINTF)

%.o: %.c
	@$(GCC) -c $^ -I./includes/

$(NAME) :	$(EXEC) $(OBJ)
	@gcc $(OBJ) -o $(NAME) -L $(EXEC_PRINTF) -lftprintf -L $(EXEC_LFT) -lft -lncurses -I./includes
	@echo "$@ was created"

clean :
	@$(MAKE) $@	-C $(EXEC_LFT)
	@$(MAKE) $@	-C $(EXEC_PRINTF)
	@$(RM) $(OBJ)

fclean : clean
	@$(MAKE) $@	-C $(EXEC_LFT)
	@$(MAKE) $@	-C $(EXEC_PRINTF)
	@$(RM) $(NAME)

re :	fclean	all

here :
	$(RM) $(OBJ) $(NAME)
