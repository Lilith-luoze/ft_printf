NAME := libftprintf.a
HDRS := ft_printf.h

CC := cc
CFLAGS := -Wall -Wextra -Werror

AR := ar
ARFLAGS := rcs
# TO BE MODIFIED: 
SRCS := ft_printf.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_puthex.c \
		ft_putptr.c \
		ft_putunsigned.c


OBJS := $(SRCS:.c=.o)
.DEFAULT_GOAL := all
.PHONY: all re clean fclean # bonus
# five mandaroty targets
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

all: $(NAME)

%.o:%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
