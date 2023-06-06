/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/06 15:45:06 by jyim             ###   ########.fr       */
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
			while (input[++i])
			{
				if (input[i] == quote_type)
				{
					boolean = 0;
					break ;
				}
			}
		}
	}
	return (boolean);
}

char	*insert_line(char *input)
{
	char	*nextline;
	char	*tmp_input;
	char	*new_input;

	tmp_input = input;
	nextline = readline(">");
	new_input = ft_strjoin(input, "\n");
	new_input = ft_strjoin(new_input, nextline);
	free(tmp_input);
	printf("New Input: %s\n", new_input);
	return (new_input);
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
void	input_commands(char **splitted, t_cmd **cmdgroups)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (splitted[i])
	{
		if (is_rdr(splitted[i]))
		{
			(*cmdgroups)[j].rdr = is_rdr(splitted[i++]);
			if (is_pipes(splitted[i]))
				exit_error();
			(*cmdgroups)[j].rdr_filename = ft_strdup(splitted[i]);
			if (!is_pipes(splitted[i]))
			{
				j++;
				continue;
			}
		}
		(*cmdgroups)[j].args = ft_append_2d((*cmdgroups)[i].args, splitted[i]);
	}
}

void	init_cmdgroupsv2(char **splitted, t_cmd **cmdgroups)
{
	int		i;
	int		pipes;

	i = 0;
	pipes = has_pipes(splitted);
	printf("Number of pipes: %d\n", pipes);
	*cmdgroups = (t_cmd *)malloc (sizeof(t_cmd) * (pipes + 2));
	while (i < (pipes + 2))
	{
		(*cmdgroups)[i].args = NULL;
		(*cmdgroups)[i].rdr = NULL;
		(*cmdgroups)[i].rdr_filename = NULL;
	}
	input_commands(splitted, cmdgroups);
}

void	parse_cmds(char *input, t_cmd *cmdgroups)
{
	char	**splitted;
	

	printf("Input before split: %s$\n", input);
	splitted = ft_split_quoted(input, ' ');
	int	k = -1;
	while (splitted[++k])
		printf("splitted %d: %s$\n", k, splitted[k]);
	init_cmdgroupsv2(splitted, &cmdgroups);
}
