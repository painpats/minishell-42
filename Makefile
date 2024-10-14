# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 14:34:47 by ecorvisi          #+#    #+#              #
#    Updated: 2023/08/30 15:39:37 by ecorvisi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -Wunreachable-code -g3
CPPFLAGS = -Iinc

NAME = minishell
LIB = libft/libft.a
LIBFT_FLAGS = -L libft -lft

SRC_DIR = src
OBJ_DIR = obj
DIR_OBJS = mkdir -p $(@D)

SRC = 	my_prompt.c \
		parsing/parse.c \
		parsing/check_parsing.c \
		parsing/check_parsing_2.c \
		parsing/parse_utils.c \
		lexer/lexer.c \
		lexer/lexer_2.c\
		files.c \
		files_2.c \
		here_doc/here_doc.c \
		here_doc/check_here_doc.c \
		here_doc/here_doc_limiter.c \
		here_doc/ft_read_heredoc.c \
		utils/init.c \
		utils/utils.c \
		utils/ft_split_quote.c \
		utils/ft_split_ws_quote.c\
		utils/getenv.c \
		utils/expand.c \
		utils/expand_utils.c \
		exec/exec.c \
		exec/open.c \
		exec/exec_utils.c \
		exec/child.c \
		exec/child_utils.c \
		exec/child_builtins.c \
		exec/exec_single.c \
		free/free.c \
		free/free2.c \
		free/close.c \
		builtins/ft_env.c \
		builtins/ft_pwd.c \
		builtins/ft_exit.c\
		builtins/ft_cd.c \
		builtins/ft_unset.c \
		builtins/ft_echo.c \
		builtins/export/ft_export.c \
		builtins/export/ft_export_2.c \
		builtins/export/ft_check_export.c \
		signals/signals.c \

SRCS = $(SRC:%=$(SRC_DIR)/%)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;4m\033[1;33m                       \033[0m"
	@echo "\033[1;4m\033[1;33m\033[1;1m*      COMPILING      *\033[0m"
	@make bonus -s -C libft
	@$(CC) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(LIB) -lreadline
	@echo "\033[1;4m\033[1;32m                                \033[0m"
	@echo "\033[1;4m\033[1;32m\033[1;1m*      MINISHELL COMPILED      *\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJS) $(OBJ_DIR)
	@make clean -s -C libft
	@echo "\033[1;4m\033[1;34m                                     \033[0m"
	@echo "\033[1;4m\033[1;34m\033[1;1m*      DELETING OBJS DIRECTORY      *\033[0m"
	
fclean:
	@rm -rf $(OBJS) $(OBJ_DIR)
	@rm -rf $(NAME)
	@make fclean -s -C libft
	@echo "\033[1;4m\033[1;31m                                 \033[0m"
	@echo "\033[1;4m\033[1;31m\033[1;1m*      CLEANING ALL BINARY      *\033[0m"

re: fclean all

.PHONY: all clean fclean re
