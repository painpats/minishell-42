# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbourre <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 11:28:43 by cbourre           #+#    #+#              #
#    Updated: 2022/04/13 10:45:20 by cbourre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a

SRCS = 		ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strncmp.c \
			ft_memcmp.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_memchr.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_itoa.c \
			ft_split.c \
			ft_print_char.c \
			ft_print_dec.c \
			ft_print_dec_uns.c \
			ft_print_hexa.c \
			ft_print_ptr.c \
			ft_print_str.c \
			ft_printf.c

BONUS =		ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

HEADERS =	libft.h

CC =		gcc -g

CFLAGS =	-Wall -Wextra -Werror

CLIB =		ar -rcs

RM =		rm -f

OBJ =		$(SRCS:.c=.o)

BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CLIB) $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	$(CLIB) $(NAME) $(BONUS_OBJ)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
