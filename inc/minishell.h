/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:43 by jyim              #+#    #+#             */
/*   Updated: 2023/06/13 12:19:27 by sulim            ###   ########.fr       */
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
# define OPERATORS		"|><&()"
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

// /* Parse Info */
// typedef struct s_parse
// {
// 	char			**cmd;
// 	int				type;
// 	struct s_parse	*next;
// }				t_parse;

typedef enum s_rdrtype
{
	IN = 1,
	OUT = 2,
	HEREDOC = 3,
	APPEND = 4,
}	t_rdrtype;

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
	int				rdr;
	char			*rdr_filename;
	t_rdrinfo		*rdr_info;
}				t_cmd;

/* Env Info */
typedef struct s_env
{
	char	**env;
	char	**path;
	int		nos_pipe;
	t_cmd	*cmdgroups;
}				t_env;

// Pipex
typedef struct s_pipex
{
	pid_t 		pid;
	int			pipes[2];
	char		*paths;
	char		**cmd_path;
	char		*cmd;
	char		**cmd_args;
}	t_pipex;

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

// pipex
void ft_pipex(char *input, t_pipex *pipex);
void parent();
void child();

#endif