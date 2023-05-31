/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/05/31 12:01:37 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			boolean = 1;
			quote_type = input[i];
			while (input[++i])
			{
				if (input[i] == quote_type)
				{
					boolean = 0;
					break;
				}
			}
		}
		if (input[i] == '\0')
			break ;
	}
	// printf("Check Quotes: %d\n", boolean);
	return (boolean);
}

char	*insert_line(char *input)
{
	char *nextline;
	char *tmp_input;
	char *new_input;

	tmp_input = input;
	nextline = readline(">");
	new_input = ft_strjoin(input, "\n");
	new_input = ft_strjoin(new_input, nextline);
	free(tmp_input);
	printf("New Input: %s\n", new_input);
	return (new_input);
}

init_cmdgroups(char *input, t_cmd **cmdgroups)
{
	int	i;
	int pipes;
	char	quote_type;
	i = -1;
	pipes = 0;
	while(input[++i])
	{
		if(input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			quote_type = input[i];
			while (input[++i])
			{
				if (input[i] == quote_type)
					break;
			}
		}
		if(input[i] == '|')
			pipes++;
		if (input[i] == '\0')
			break ;
	}
	printf("%d\n", pipes);
	cmdgroups = (t_cmd **)malloc (sizeof(t_cmd *) * pipes + 2);
	cmdgroups[pipes + 1]->args = NULL;
	}

// void parse_cmds(char *input, t_cmd *cmdgroups)
// {
// 	init_cmdgroups(input, &cmdgroups);
	
// }

// int	check_num_closed_quotes(c)