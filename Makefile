# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 19:08:52 by ialvarez          #+#    #+#              #
#    Updated: 2023/03/06 17:06:38 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

SRCS = ./main.c \
       ./liberator/liberator.c \
       ./parse/parse.c \
       ./parse/expand_parser.c \
       ./parse/redir_parser.c \
       ./errors/syntax_err.c \
       ./tokenizator/init_variables.c \
       ./tokenizator/tokenizator.c \
       ./tokenizator/heredoc.c \
       ./tokenizator/redirec.c \
       ./tokenizator/take_args.c \
       ./tokenizator/tokenizator_utils.c \
       ./tokenizator/rm_used.c \
       ./tokenizator/aux_key.c \
       ./builtins/pwd.c \
       ./builtins/echo.c \
       ./builtins/env.c \
       ./builtins/exit.c \
       ./builtins/cd.c \
       ./builtins/unset.c \
       ./builtins/bultins_utils.c \
       ./builtins/export.c \
       ./exec/handle_signal.c \
       ./exec/exec_builtins.c \
       ./exec/exec.c

OBJECTS = $(SRCS:.c=.o)
LIBFT_DIR = libft/
PRINTF_DIR = printf/
LIB_NAME = $(LIBFT_DIR)libft.a
PRINTF_NAME = $(PRINTF_DIR)libftprintf.a
INCLUDES = -I. -I $(LIBFT_DIR) -I $(PRINTF_DIR)
FSANITIZE = -g3 -fsanitize=address
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
CFLAGS = -Wall -Werror -Wextra -I /Users/$(USER)/.brew/opt/readline/include -g3 $(INCLUDES)

BCyan = \033[1;36m
GREEN = \033[0;32m
Yellow = \033[0;33m
Red = \033[0;31m
NO_COLOR = \033[0m

#.SILENT:

all: $(NAME)

$(LIB_NAME):
	@make -s -C $(LIBFT_DIR)

$(PRINTF_NAME):
	@make -s -C $(PRINTF_DIR)

$(NAME): $(OBJECTS) $(LIB_NAME) $(PRINTF_NAME)
	@$(CC) $(CFLAGS) $(READLINE) $(OBJECTS) $(PRINTF_NAME) $(LIB_NAME) -o $(NAME)
	@echo "$(GREEN)[COMPILED]$(NO_COLOR)"

clean:
	@echo "$(Yellow)[CLEAN]$(NO_COLOR)"
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(PRINTF_DIR) clean
	@rm -f $(OBJECTS)

fclean: clean
	@echo "$(Red)[FCLEAN]$(NO_COLOR)"
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
