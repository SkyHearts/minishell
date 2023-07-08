/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:41 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 10:51:04 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	unsigned_operators(char *split)
{
	if (split[0] == '>' || split[0] == '<' || split[0] == '|')
	{
		if (is_operator(split) == 0)
		{
			printf("syntax error near unexpected token '%s'\n", split);
			return (258);
		}
	}
	return (0);
}

int	pipe_operators(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{	
		if (is_operator(split[i]) && split[i + 1] == NULL)
		{
			if (ft_strcmp(split[0], "echo"))
				return (printf("syntax error near unexpected token 'newline' \
				\n"), 258);
		}
		else if (is_operator(split[i]) && is_pipes(split[i + 1]))
			return (printf("syntax error near unexpected token '%s'\n", \
			split[i + 1]), 258);
		else if (is_rdr(split[i]) && is_rdr(split[i + 1]))
			return (printf("syntax error near unexpected token '%s'\n", \
			split[i + 1]), 258);
		i++;
	}
	return (0);
}
		// else if (split[i + 2] == NULL || is_operator(split[i + 2]))
		// 	return (printf("syntax error near unexpected token '%s'\n",
		// split[i]), 258);

int	syntax_checking(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (!is_operator(split[i]))
		{
			if (unsigned_operators(split[i]) == 258)
				return (258);
		}
	}
	if ((pipe_operators(split)) == 258)
		return (258);
	return (0);
}

//int	rdr_operators(char *s, char *s_plus_1, char *s_plus_2)
//{
//	if (is_operator(s_plus_1) == 3)
//		printf("syntax error near unexpected token 'newline'\n");
//	else if (is_pipes(s) && is_operator(s_plus_1))
//	{
//		if (!is_operator(s_plus_2))
//			return (0);
//		printf("syntax error near unexpected token here2'%s'\n",
//			s);
//	}
//	return (258);
//}