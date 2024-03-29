NAME	= minishell
CC		= gcc
FSAN	= -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -g3
INCLUDES = -I inc -I ${LIBFT_DIR} -I ${PRINT_DIR} -I/usr/local/opt/readline/include
READLINE	= -lreadline -L/usr/local/opt/readline/lib 

SHELL_SRCS	=	minishell.c pipe.c multipipe.c pipe_utils.c signal.c hdoc_handler.c rdr.c
SHELL_SRCS_DIR	= src/
SHELL_OBJS = $(addprefix $(SHELL_SRCS_DIR), $(SHELL_SRCS:.c=.o))

BUILTINS_SRC = echo.c cd.c env.c exit.c export.c pwd.c unset.c
BUILTINS_DIR = src/builtins/
BUILTINS_OBJS = $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC:.c=.o))

EXPAND_SRC = dollar.c expander.c tokenize.c
EXPAND_DIR = src/expander/
EXPAND_OBJS = $(addprefix $(EXPAND_DIR), $(EXPAND_SRC:.c=.o))

PARSE_SRC = parsing.c ft_split_quote.c parse_utils.c
PARSE_DIR = src/parsing/
PARSE_OBJS = $(addprefix $(PARSE_DIR), $(PARSE_SRC:.c=.o))

UTILS_SRC = env.c free.c utils.c utils_2.c utils_3.c utils_4.c utils_5.c
UTILS_DIR = src/utils/
UTILS_OBJS = $(addprefix $(UTILS_DIR), $(UTILS_SRC:.c=.o))

LIBFT_DIR		= utils/libft
LIBFT_LIB		= libft.a
LIB             = -L$(LIBFT_DIR) -lft

PRINT_DIR		= utils/ft_printf
PRINT_LIB		= libftprintf.a
PRINT            = -L$(PRINT_DIR) -lftprintf

all:  ${NAME}

${NAME}:	${LIBFT_DIR}/${LIBFT_LIB} ${PRINT_DIR}/${PRINT_LIB} ${SHELL_OBJS} ${BUILTINS_OBJS} ${EXPAND_OBJS} ${PARSE_OBJS} ${UTILS_OBJS} 
	@echo "Compiling minishell"
	${CC} ${CFLAGS} ${SHELL_OBJS} ${BUILTINS_OBJS} ${EXPAND_OBJS} ${PARSE_OBJS} ${UTILS_OBJS} -o ${NAME} ${LIB} ${PRINT} ${READLINE}
	
${LIBFT_DIR}/${LIBFT_LIB}:
	@make -C ${LIBFT_DIR}

${PRINT_DIR}/${PRINT_LIB}:
	@make -C ${PRINT_DIR}

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@make clean -C ${PRINT_DIR}
	@rm -rf ${SHELL_OBJS}
	@rm -rf ${BUILTINS_OBJS}
	@rm -rf ${EXPAND_OBJS}
	@rm -rf ${PARSE_OBJS}
	@rm -rf ${UTILS_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@make fclean -C ${PRINT_DIR}
	@rm -rf ${NAME}

re: clean all

.PHONY:	all clean fclean re 