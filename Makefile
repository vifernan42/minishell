# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 19:08:52 by ialvarez          #+#    #+#              #
#    Updated: 2022/08/04 13:06:36 by vifernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

SRCS = main.c \
	   ./parse/parse.c \
	   ./tokenizator/tokenizator.c \
	   ./tokenizator/heredoc.c \
	   ./errors/syntax_err.c \
	   ./tokenizator/redirec.c \
	   ./tokenizator/take_args.c \
	   ./tokenizator/tokenizator_utils.c \

OBJECTS = $(SRCS:.c=.o)
LIBFT_DIR = libft/
PRINTF_DIR = printf/
LIB_NAME = $(LIBFT_DIR)libft.a
PRINTF_NAME = $(PRINTF_NAME)libftprintf.a
INCLUDES = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)
FSANITIZE = -g3 -fsanitize=address
READLINE = -L ~/.brew/opt/readline/lib -lreadline
CFLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include $(INCLUDES)

all: $(NAME)

BCyan = \033[1;36m
GREEN = \033[0;32m
Yellow = \033[0;33m
Red = \033[0;31m
NO_COLOR = \033[0m

$(NAME): $(OBJECTS)
	@echo "$(BCyan)[COMPILED]$(NO_COLOR)"
	@make -s -C $(LIBFT_DIR) 
	@make -s -C $(PRINTF_DIR)
	@$(CC) $(READLINE) $(CFLAGS) $(OBJECTS) ./printf/libftprintf.a \
											./libft/libft.a -o $(NAME)

debug: fclean all
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(PRINTF_DIR)
	@$(CC) $(READLINE) $(CFLAGS) $(FSANITIZE) $(OBJECTS) ./printf/libftprintf.a \
								./libft/libft.a -o $(NAME)
	@./minishell				

clean:
	@echo "$(Yellow)[CLEAN]$(NO_COLOR)"
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@rm -f $(OBJECTS)

fclean: clean
	@echo "$(Red)[FCLEAN]$(NO_COLOR)"
	@make -C $(LIBFT_DIR) fclean
	@make -C$(PRINTF_DIR) fclean
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
