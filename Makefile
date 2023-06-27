NAME	= minishell
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -fsanitize=address -g3 
INCLUDES = -I inc -I ${LIBFT_DIR} -I/usr/local/opt/readline/include
READLINE	= -lreadline -L/usr/local/opt/readline/lib 

LIBFT_DIR		= utils/libft
LIBFT_LIB		= libft.a

#PRINT_DIR		= inc/ft_printf
#PRINT_LIB		= libftprintf.a

SHELL_SRCS	=	minishell.c utils.c env.c expander.c ft_split_quote.c init.c parsing.c tokenize.c pipe.c \
				signal.c
SHELL_SRCS_DIR	= src/
SHELL_OBJS = $(addprefix $(SHELL_SRCS_DIR), $(SHELL_SRCS:.c=.o))

BUILTINS_SRC = echo.c cd.c env.c exit.c export.c pwd.c unset.c
BUILTINS_DIR = src/builtins/
BUILTINS_OBJS = $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC:.c=.o))

all: ${NAME}

${LIBFT_DIR}/${LIBFT_LIB}:
	@echo "Compilling libft"
	@make -C ${LIBFT_DIR}

#${PRINT_DIR}/${PRINT_LIB}:
#	@echo "Compilling printf"
#	@make -C ${PRINT_DIR}

${NAME}:	${PRINT_DIR}/${PRINT_LIB} ${LIBFT_DIR}/${LIBFT_LIB} ${SHELL_OBJS} ${BUILTINS_OBJS}
	@echo "Compiling minishell"
	${CC} ${CFLAGS} ${SHELL_OBJS} ${BUILTINS_OBJS} -o ${NAME} ${READLINE} -L${LIBFT_DIR} -lft 

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${SHELL_OBJS}
	@rm -rf ${BUILTINS_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}

re: clean all

.PHONY:	all clean fclean re 