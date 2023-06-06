NAME	= minishell
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -fsanitize=address -g3 -lreadline
INCLUDES = -I inc -I ${LIBFT_DIR}

LIBFT_DIR		= utils/libft
LIBFT_LIB		= libft.a

#PRINT_DIR		= inc/ft_printf
#PRINT_LIB		= libftprintf.a

SHELL_SRCS	=	minishell.c env.c expander.c ft_split_quote.c init.c parsing.c tokenize.c 
SHELL_SRCS_DIR	= src/
SHELL_OBJS = $(addprefix $(SHELL_SRCS_DIR), $(SHELL_SRCS:.c=.o))

all: ${NAME}

${LIBFT_DIR}/${LIBFT_LIB}:
	@echo "Compilling libft"
	@make -C ${LIBFT_DIR}

#${PRINT_DIR}/${PRINT_LIB}:
#	@echo "Compilling printf"
#	@make -C ${PRINT_DIR}

${NAME}:	${PRINT_DIR}/${PRINT_LIB} ${LIBFT_DIR}/${LIBFT_LIB} ${SHELL_OBJS} 
	@echo "Compiling minishell"
	${CC} ${CFLAGS} ${SHELL_OBJS} -o ${NAME} -L${LIBFT_DIR} -lft

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@make clean -C ${PRINT_DIR}
	@rm -rf ${SHELL_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@make fclean -C ${PRINT_DIR}

re: clean all

.PHONY:	all clean fclean re 