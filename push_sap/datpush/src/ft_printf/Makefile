#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/13 10:05:24 by abombard          #+#    #+#              #
#    Updated: 2015/02/04 19:29:48 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= 	gcc -Wall -Wextra -Werror -O
RM= 	rm -f
SRC=	ft_printf.c \
		init_args.c \
		init_flags.c \
		init_opt.c \
		my_putnbr_base.c \
		my_strcapitalize.c \
		wchar.c \
		case1.c \
		case2.c \
		prec_field.c \
		care_flags.c \
		annexe.c \

OBJ=	$(SRC:.c=.o)
NAME=	libftprintf.a
EXEC=	libft

.PHONY: $(EXEC)

all :	$(EXEC) $(NAME)

$(EXEC):
	@$(MAKE) -C libft/

%.o: %.c
	@$(GCC) -c $^ -I./../../includes/
	@echo "\033[0;33m$@ was created\033[0m"

$(NAME) :	$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean :
	@$(MAKE) $@	-C libft/
	@$(RM) $(OBJ)

fclean : clean
	@$(MAKE) $@ -C libft/
	@$(RM) $(NAME)

re :	fclean	all

here :
	$(RM) $(OBJ) $(NAME)
