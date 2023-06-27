/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/27 11:27:01 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	if_quotes(char input)
{
	if (input == SINGLE_QUOTE || input == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	check_quotes(char *input)
{
	char	quote_type;
	int		boolean;
	int		i;

	i = -1;
	quote_type = -1;
	boolean = 0;
	while (input[++i])
	{
		if (if_quotes(input[i]))
		{
			boolean = 1;
			quote_type = input[i];
			while (input[++i] && input[i] != quote_type)
				continue ;
			if (!input[i])
				return (boolean);
			boolean = 0;
		}
	}
	return (boolean);
}

void	rdr_to_cmdgroups(t_rdrinfo *rdr_info, char **s, int *start, int end)
{
	int	i;

	i = 0;
	while (s[(*start)] && (*start) < end)
	{
		if (is_rdr(s[(*start)]))
		{
			(rdr_info)[i].rdr_type = is_rdr(s[(*start)++]);
			(rdr_info)[i].rdr_str = ft_strdup(s[(*start)]);
			printf("rdr_type: %d\n", (rdr_info)[i].rdr_type);
			printf("rdr_str: %s\n", (rdr_info)[i].rdr_str);
			i++;
		}
		(*start)++;
	}
	rdr_info[i].rdr_str = NULL;
	rdr_info[i].rdr_type = EMPTY;
}

void	input_rdr(char **splitted, t_pipe *cmdgroups)
{
	int			i;
	int			j;
	int			num_rdr;
	int			start;
	t_rdrinfo	*info;

	i = -1;
	j = 0;
	num_rdr = 0;
	start = 0;
	// printf("AT INPUT_RDR\n");
	while (splitted[++i])
	{
		if (is_pipes(splitted[i]) || splitted[i + 1] == NULL)
		{
			info = (t_rdrinfo *)malloc (sizeof(t_rdrinfo) * (num_rdr + 1));
			rdr_to_cmdgroups(info, splitted, &start, i);
			cmdgroups[j].rdr_info = info;
			num_rdr = 0;
			j++;
		}
		else if (is_rdr(splitted[i]))
			num_rdr++;
	}
}

/* Parse all input into cmdgroups */
void	input_commands(char **splitted, t_pipe *cmdgroups)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	// printf("AT INPUT_COMMANDS\n");
	while (splitted[++i])
	{	
		if (is_rdr(splitted[i]))
			i++;
		else if (!is_rdr(splitted[i]) && !is_pipes(splitted[i]))
		{
			// printf("current splited[%d]: %s\n",i, splitted[i]);
			(cmdgroups)[j].args = ft_append_2d
				((cmdgroups)[j].args, splitted[i]);
		}
		else if (is_pipes(splitted[i]) && splitted[i])
			j++;
	}
	if (!(cmdgroups)[j].args)
	{
		(cmdgroups)[j].args = malloc (sizeof(char *));
		(cmdgroups)[j].args[0] = NULL;
	}
}

void	init_pipegroupsv2(char **splitted, t_env *env_table)
{
	int		i;
	t_pipe	*cmdgroups;

	i = -1;
	env_table->nos_pipe = has_pipes(splitted);
	env_table->cmdgroups = (t_pipe *)malloc (sizeof(t_pipe)
			* (env_table->nos_pipe + 1));
	cmdgroups = env_table->cmdgroups;
	while (++i < (env_table->nos_pipe) + 1)
	{
		(cmdgroups)[i].args = NULL;
		(cmdgroups)[i].rdr_info = NULL;
		(cmdgroups)[i].rdr_count = 0;
	}
	input_commands(splitted, cmdgroups);
	input_rdr(splitted, cmdgroups);
}

int	syntax_checking(char **splitted)
{
	int	i;

	i = -1;
	while (splitted[++i])
	{
		if (is_operator(splitted[i]))
		{
			if (!ft_strncmp(splitted[i], ">>>", 3))
				return (printf("syntax error near unexpected token >>>\n"), 1);
			if (!ft_strncmp(splitted[i], "<<<", 3))
				return (printf("syntax error near unexpected token <<<\n"), 1);
		}
		if (is_operator(splitted[i]) && !splitted[i + 1])
		{
			if (is_pipes(splitted[i]))
				printf("syntax error near unexpected token '%s'\n", splitted[i]);
			else
				printf("syntax error near unexpected token 'newline'\n");
			return (1);
		}
		if (is_operator(splitted[i]) && is_operator(splitted[i + 1]))
		{
			if (is_operator(splitted[i + 1]) == 3)
				printf("syntax error near unexpected token 'newline'\n");
			else
				printf("syntax error near unexpected token '%s'\n", splitted[i + 1]);
			return (1);
		}
	}
	return (0);
}

char	*find_env_cont(char *splitted, int start, t_env *env_table, char **str)
{
	int		i;
	int		end;
	char	*env_var;
	int		offset;
	char	*err_num;
	
	i = -1;
	end = start++;
	while (splitted[++end] && ft_isalnum_q(splitted[end]) && !if_quotes(splitted[end]))
		continue ;
	env_var = ft_substr(splitted, start, end - start);
	offset = ft_strlen(env_var);
	if (!ft_strcmp(env_var, "?"))
	{
		err_num = ft_itoa(env_table->errnumber);
		(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
					+ ft_strlen(err_num) + 1));
		return (free(env_var), err_num);
	}
	while (env_table->env[++i])
	{	
		if (!ft_strncmp(env_var, (env_table->env[i]), offset) && env_table->env[i][offset] == '=')
		{
			(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
					+ ft_strlen(env_table->env[i] + offset) + 1));
			return (free(env_var), ft_strdup(env_table->env[i] + offset + 1));
		}
	}
	(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
					 + 1));
	if (!(*str))
		printf("Malloc failed");
	return (free(env_var), ft_strdup(""));
}

char	*find_env_var(char *s, int start)
{
	int		i;
	int		end;
	char	*env_var;

	i = -1;
	end = start;
	while (s[++end] && !if_quotes(s[end]) && ft_isalnum_q(s[end]))
		continue ;
	env_var = ft_substr(s, start, end - start);
	return (env_var);
}

char	*replace_sign(char *splitted, int start, t_env *env_table)
{
	int		i;
	char	*env_cont;
	char	*env_var;
	char	*str;

	i = 0;
	env_var = find_env_var(splitted, start);
	printf("env_var : %s\n", env_var);
	env_cont = find_env_cont(splitted, start, env_table, &str);
	printf("env_cont : %s\n", env_cont);
	str = ft_strncpy(str, splitted, start);
	str = ft_strcat(str, env_cont);
	str = ft_strcat(str, splitted + ft_strlen(env_var) + start);
	free(splitted);
	free(env_cont);
	free(env_var);
	return (str);
}

void	handle_dollarsign(char **splitted, t_env *env_table)
{
	int	i;
	int	j;
	char quote_type;

	i = -1;
	quote_type = '\0';
	while (splitted[++i])
	{
		j = -1;
		while (splitted[i][++j])
		{
			if (if_quotes(splitted[i][j]))
			{
				quote_type = splitted[i][j];
				if (splitted[i][j] == SINGLE_QUOTE)
				{
					while (splitted[i][++j] && splitted[i][j] != SINGLE_QUOTE)
						continue ;
				}
				if (splitted[i][j] == DOUBLE_QUOTE)
				{
					while (splitted[i][++j] && splitted[i][j] != DOUBLE_QUOTE)
					{
						if (splitted[i][j] == '$')
							splitted[i] = replace_sign(splitted[i], j, env_table);
					}
				}
			}
			if (splitted[i][j] == '$')
				splitted[i] = replace_sign(splitted[i], j, env_table);
			if (splitted[i][j] == '\0')
				break ;
		}
	}	
}

int	parse_cmds(char *input, t_env *env_table)
{
	char	**splitted;

	printf("Input before split: %s$\n", input);
	splitted = ft_split_quoted(input, ' ');
	printf("Input after split: %s$\n", input);
	if (!ft_strcmp(input, "") || syntax_checking(splitted))
		return (1);
	handle_dollarsign(splitted, env_table);
	// int	k = -1;
	// while (splitted[++k])
	// 	printf("splitted %d: [%s]\n", k, splitted[k]);
	init_pipegroupsv2(splitted, env_table);
	return (0);
}
