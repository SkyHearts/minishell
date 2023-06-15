/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/14 16:01:47 by jyim             ###   ########.fr       */
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

/* void	init_cmdgroupsv1(char *input, t_cmd **cmdgroups)
{
	int		i;
	int		pipes;
	char	quote_type;

	i = -1;
	pipes = 0;
	while (input[++i])
	{
		if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			quote_type = input[i];
			while (input[++i])
			{
				if (input[i] == quote_type)
					break ;
			}
			continue ;
		}
		if (input[i] == '|')
			pipes++;
	}
	printf("Number of pipes: %d\n", pipes);
	*cmdgroups = (t_cmd *)malloc (sizeof(t_cmd) * (pipes + 2));
	(*cmdgroups)[pipes + 1].args = NULL;
} */

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

void	input_rdr(char **splitted, t_cmd *cmdgroups)
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
	printf("AT INPUT_RDR\n");
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
void	input_commands(char **splitted, t_cmd *cmdgroups)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	printf("AT INPUT_COMMANDS\n");
	while (splitted[++i])
	{	
		if (is_rdr(splitted[i]))
			i++;
		else if (!is_rdr(splitted[i]) && !is_pipes(splitted[i]))
		{
			printf("current splited[%d]: %s\n",i, splitted[i]);
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

void	init_cmdgroupsv2(char **splitted, t_env *env_table)
{
	int		i;
	t_cmd	*cmdgroups;

	i = -1;
	env_table->nos_pipe = has_pipes(splitted);
	printf("Number of pipes: %d\n", env_table->nos_pipe);
	env_table->cmdgroups = (t_cmd *)malloc (sizeof(t_cmd)
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
		if(is_operator(splitted[i]) && !splitted[i + 1])
		{
			if (is_pipes(splitted[i]))
				printf("syntax error near unexpected token '%s'\n", splitted[i]);
			else
				printf("syntax error near unexpected token 'newline'\n");
			return (1);
		}
		if(is_operator(splitted[i]) && is_operator(splitted[i + 1]))
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

int	parse_cmds(char *input, t_env *env_table)
{
	char	**splitted;

	printf("Input before split: %s$\n", input);
	splitted = ft_split_quoted(input, ' ');
	// int	k = -1;
	// while (splitted[++k])
	// 	printf("splitted %d: %s$\n", k, splitted[k]);
	if (!ft_strcmp(input, "") || syntax_checking(splitted))
		return (1);
	init_cmdgroupsv2(splitted, env_table);
	return (0);
}
