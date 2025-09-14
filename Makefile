# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 16:43:22 by luozguo           #+#    #+#              #
#    Updated: 2025/09/14 19:11:46 by luozguo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
HDRS := ft_printf.h

CC := cc
CFLAGS := -Wall -Wextra -Werror
AR := ar
ARFLAGS := rcs
RM      := rm -f

SRCS := ft_printf.c parser.c dispatcher.c put_helpers_1.c put_helpers_2.c \
		put_helpers_3.c put_c.c put_s.c put_d.c put_u.c put_hex.c put_p.c put_percent.c

OBJS := $(SRCS:.c=.o)
.DEFAULT_GOAL := all

.PHONY: all re clean fclean bonus

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

all: $(NAME) 

%.o:%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all
