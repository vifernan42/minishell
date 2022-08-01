# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 19:08:52 by ialvarez          #+#    #+#              #
#    Updated: 2022/08/01 16:55:13 by ialvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

SRCS = main.c \
	   ./parse/parse.c \
	   ./tokenizator/tokenizator.c \
	   ./tokenizator/heredoc.c \
	   ./tokenizator/rm_arg_quotes.c \
	   ./errors/syntax_err.c \

#	echo.c \
		#pwd.c \
		main.c \

OBJECTS = $(SRCS:.c=.o)
LIBFT_DIR = libft/
LIB_NAME = $(LIBFT_DIR)libft.a
INCLUDES = -I. -I$(LIBFT_DIR)
FSANITIZE = -g3 -fsanitize=address
READLINE = -L ~/.brew/opt/readline/lib -lreadline
CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include -g3 $(INCLUDES)

all: $(NAME)

BCyan = \033[1;36m
GREEN = \033[0;32m
Yellow = \033[0;33m
Red = \033[0;31m
NO_COLOR = \033[0m

$(NAME): $(OBJECTS)
	@echo "$(BCyan)[COMPILED]$(NO_COLOR)"
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(READLINE) $(CFLAGS) $(OBJECTS) ./libft/libft.a -o $(NAME)

debug: $(OBJECTS)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(FSANITIZE) $^ -L ./libft/ -l ft -o $(NAME)


clean:
	@echo "$(Yellow)[CLEAN]$(NO_COLOR)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJECTS)

fclean: clean
	@echo "$(Red)[FCLEAN]$(NO_COLOR)"
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

test: fclean all
	@echo "$(GREEN)[RESULTS]$(NO_COLOR)"
	@./minishell

re: fclean all

.PHONY:
			clean
			fclean
			all
			re
			bonus
