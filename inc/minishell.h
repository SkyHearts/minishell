/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:43 by jyim              #+#    #+#             */
/*   Updated: 2023/07/06 16:33:36 by sulim            ###   ########.fr       */
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
# include "../utils/libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

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
typedef int	(*t_function)(struct s_env *env_table, char **argv);

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
typedef struct s_pipe
{
	char			*cmd;
	char			**args;
	int				rdr_count;
	t_rdrinfo		*rdr_info;
}				t_pipe;

/*<file1  cat | wc -l >file2*/
/* Env Info */
typedef struct s_env
{
	char		**env;
	char		**path;
	int			nos_pipe;
	char		**functions;
	int			errnumber;
	char		**rl_buffer;
	char		**hdoc;
	t_pipe		*cmdgroups;
	t_pipe		*pipe;
	t_function	func[7];
}				t_env;

/* env function */
char	**dup_env(char **env);
char	**extract_path(t_env *env, char **env_table);
void	print_darray(char **array);

/* Input Manipulations */
char	*expand_operators(char *s);
void	store_rl_buffer(char *input, t_env *env_table);

/* Parsing */
/* quotes split */
char	*insert_line(char *input, t_env *env_table);
int		if_quotes(char input);
int		check_quotes(char *input);
char	**ft_split_quoted(char *input, char delim);
int		parse_cmds(char *input, t_env *env_table);
void	print_darray(char **array);
//char	*reduce_white_spaces(char *s, int need_free);
void 	reduce_white_spaces_3(char *s);
void	exit_error(void);
int		syntax_checking(char **splitted);

/* Signal */
void	init_signal(void);
void	sig_handler(int signum);
void	sig_handler_nl(int signum);

/* Utils */
int		has_pipes(char **splitted);
int		is_rdr(char *splitted);
int		is_pipes(char *splitted);
int		if_quotes(char input);
int		ft_char_cmp_str(char s, char *op_list);
int		is_operator(char *str);
int		ft_isalpha_equal(int c);
int		ft_isalnum_q(int c);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strjoin_f(char *s1, char *s2);
void	error(char *err);
void	free_doublearray(char **array);
char	*ft_strdup_quote(const char *src);
char	**ft_append_2d(char **args, char *str);
char	**ft_append_2d_nf(char **args, char *str);
size_t	ft_strlen_n(const char *s);

/* Handle Dollar sign */
char	*find_env_cont(char *splitted, int start, t_env *env_table, char **str);
char	*find_env_var(char *s, int start);
char	*replace_sign(char *splitted, int start, t_env *env_table);
void	handle_dollarsign(char **splitted, t_env *env_table, int hdoc);

/* Handle heredoc */
char	**handle_heredoc(t_env *env_table);

// builtins
int		ft_echo(t_env *env_table, char **str);
int		ft_cd(t_env *env_table, char **str);
int		ft_pwd(t_env *env_table, char **str);
int		ft_export(t_env *env_table, char **str);
int		ft_unset(t_env *env_table, char **str);
int		ft_env(t_env *env_table, char **str);
int		ft_exit(t_env *env_table, char **str);


/* Free */
void	free_all(t_env *env_table);
void	free_var(t_env *env_table);

/* Readline Buffer Collector */
void	store_rl_buffer(char *input, t_env *env_table);
int		ft_pipe(t_env *env_table, char **env);
void	ft_dup(int m, int fd1, int fd2); 
void	multi_pipe(t_env *env_table, char **envp, int *pid);
int		check_command(t_env *env_table, int m);
void	call_cmd(t_env *env_table, t_pipe pipe, char **envp);

# define ERR_CMD "Command not found"
# define FAIL_DUP "Dup fail"
# define FAIL_PIPE "Pipe failed"
# define FAIL_WAITPID "Failed waitpid"
# define ERR_FILE "No such file in directory"

#endif