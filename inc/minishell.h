/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:43 by jyim              #+#    #+#             */
/*   Updated: 2023/05/29 17:36:56 by jyim             ###   ########.fr       */
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
# define APPEND_LEFT	"<<"
# define APPEND_RIGHT	">>"

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

/* Parse Info */
typedef struct s_cmd
{
	char			**args;
	int				rdr;
	char			*rdr_filename;
}				t_cmd;

/* Env Info */
typedef struct s_env
{
	char	**env;
	char	**path;
}				t_env;

/* env function */
char	**dup_env(char **env);
char	**extract_path(char **env_table);
void	show_env(char **env_table);

/*  */
char	*expand_operators(char *s);
char	*reduce_double_operators(char *s);
int		ft_is_double_operator(char *s, int i);

/* quotes */
char	*insert_line(char *input);
int		check_quotes(char *input);

/* spaces */
char	*reduce_white_spaces(char *s);
void	exit_error(void);

void parse_cmds(char *input, t_cmd *cmdgroups);


#endif