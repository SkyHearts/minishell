/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:43 by jyim              #+#    #+#             */
/*   Updated: 2023/06/15 13:26:55 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Library */
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include "tokenize.h"
# include "../utils/libft/libft.h"
# include <stdlib.h>
# include <string.h>

/* Operators/Commands */
# define OPERATORS		"|><"
# define PIPE			'|'
# define REDIRECT_LEFT	'<'
# define REDIRECT_RIGHT	'>'

/* Operators/Commands str */
# define APD_LEFT	"<<"	//1
# define APD_RIGHT	">>"	//2
# define RDR_LEFT	"<"		//3
# define RDR_RIGHT	">"		//4

/* Quotes */
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define EMPTY_STRING	""

// Pipe
# define PIPE_IN 0
# define PIPE_OUT 1

struct		s_env;
typedef void	(*t_function)(struct s_env *env_table, char **argv);

typedef enum s_rdrtype
{
	EMPTY = 0,
	IN = 1,
	OUT = 2,
	HEREDOC = 3,
	APPEND = 4,
}	t_rdrtype;

typedef enum e_func
{
	E_ECHO = 0,
	E_CD = 1,
	E_PWD = 2,
	E_EXPORT = 3,
	E_UNSET = 4,
	E_ENV = 5,
	E_EXIT = 6,
}	t_func;

typedef struct s_rdrinfo
{
	pid_t		rdr_pid;
	char		*rdr_str;
	t_rdrtype	rdr_type;
}				t_rdrinfo;

/* Parse Info */
typedef struct s_cmd
{
	char			**args;
	int				rdr_count;
	t_rdrinfo		*rdr_info;
}				t_cmd;

/* Env Info */
typedef struct s_env
{
	char		**env;
	char		**path;
	int			nos_pipe;
	char		**functions;
	t_cmd		*cmdgroups;
	// t_pipe		*pipe;
	t_function	func[7];
}				t_env;

/* env function */
char	**dup_env(char **env);
char	**extract_path(char **env_table);
void	show_env(char **env_table);

/* Input Manipulations */
char	*expand_operators(char *s);
char	*reduce_double_operators(char *s);
int		ft_is_double_operator(char *s, int i);

/* Utils */
int	has_pipes(char **splitted);
char **ft_append_2d(char **args, char *str);
int	is_rdr(char *splitted);
int	is_pipes(char *splitted);
int	if_quotes(char input);
int	ft_char_cmp_str(char s, char *op_list);
int	is_operator(char *str);

/* Parsing */
/* quotes */
char	*insert_line(char *input);
int		if_quotes(char input);
int		check_quotes(char *input);

/* spaces */
char	*reduce_white_spaces(char *s);
void	exit_error(void);

/* split */
char	**ft_split_quoted(char *input, char delim);

int		parse_cmds(char *input, t_env *env_table);
void	print_darray(char **array);

# define ERR_CMD "Command not found"

#endif