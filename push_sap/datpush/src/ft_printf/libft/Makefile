#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:15:17 by abombard          #+#    #+#              #
#    Updated: 2015/02/04 13:31:32 by abombard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GCC= gcc -Wall -Wextra -Werror

RM= rm -f

SRC=	ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_strlen.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_isdigit.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_isprint.c \
		ft_isascii.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_bzero.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strlcat.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strsplit.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strsort.c \
		ft_isspace.c \
		my_split_whitespace.c \
		my_stradd.c \

OBJ=	$(SRC:.c=.o)

NAME=	libft.a

all :	$(NAME)

%.o: %.c
	@$(GCC) -c $^ -I./../../../includes/
	@echo "\033[0;33m$@ was created\033[0m"

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean :
	@$(RM) $(OBJ)

fclean :
	@$(RM) $(OBJ) $(NAME)

re :	fclean	all	clean
