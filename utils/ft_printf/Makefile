NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE)
AR = ar rcs
RM = rm -f
INCLUDE = ft_printf.h

FILES = 	ft_printf \
			ft_putchar \
			ft_putnbr_dec \
			ft_putnbr_hex \
			ft_putnbr_uns_dec \
			ft_putptr \
			ft_putstr

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
