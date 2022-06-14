# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 19:08:52 by ialvarez          #+#    #+#              #
#    Updated: 2022/06/14 18:37:59 by ialvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

SRCS = echo.c pwd.c

OBJECTS = $(SRCS:.c=.o)
LIBFT_DIR = libft/
LIB_NAME = $(LIBFT_DIR)libft.a
INCLUDES = -I. -I$(LIBFT_DIR)
FSANITIZE = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $^ -L ./libft/ -l ft -o $(NAME)

debug: $(OBJECTS)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(FSANITIZE) $^ -L ./libft/ -l ft -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY:
			clean
			fclean
			all
			re
			bonus
