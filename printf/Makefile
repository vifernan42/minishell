# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 18:00:35 by ialvarez          #+#    #+#              #
#    Updated: 2022/08/02 16:03:14 by ialvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT_DIR = libft

GCC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MAKE = make

SRCS	= ft_printf.c ft_char2str.c ft_vsprintf.c ft_simple.c

OBJS	= $(SRCS:.c=.o)

all: 		$(NAME) 


$(NAME):	$(OBJS)
					$(MAKE) all -C $(LIBFT_DIR)
					cp libft/libft.a $(NAME)
					ar -rcs $(NAME) $(OBJS)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(NAME)
			$(GCC) -c $(CFLAGS) $(SRCSBN)
			ar -rcs $(NAME) $(OBJSBN)

.PHONY:
			clean
			fclean
			all
			re
			bonus
