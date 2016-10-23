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
	init_shell.c \
	check_dlinput.c \
	exec.c \
	mod_env.c \
	my_cd.c \
	my_cd2.c \
	get_next_line.c \
	strsplit_but.c \
	splitwhitespace_but.c \
	split_redirections.c \
	rebuild_tab.c \
	annexes.c \
	del_stab.c \
	outdoor.c \
	redirection.c \
	pipe.c \
	init_termcaps.c \
	lisp.c \

OBJ=$(SRC:.c=.o)
NAME=ft_minishell3
EXEC=src/ft_printf

.PHONY: $(EXEC)

all :	$(EXEC) $(NAME)

$(EXEC):
	@$(MAKE) -C $(EXEC)
	@echo "$@ was created"

%.o: %.c
	@$(GCC) -c $^ -I./includes/

$(NAME) :	$(OBJ)
	@gcc $(OBJ) -o $(NAME) -L./src/ft_printf/ -lftprintf -L./src/ft_printf/libft -lft -lncurses -I./includes
	@echo "$@ was created"

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
