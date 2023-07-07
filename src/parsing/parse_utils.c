/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:41 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 09:07:44 by jyim             ###   ########.fr       */
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
	if (!ft_strncmp(split, ">>>", 3))
		printf("syntax error near unexpected token >>>\n");
	else if (!ft_strncmp(split, "<<<", 3))
		printf("syntax error near unexpected token <<<\n");
	return (258);
}

// 0   1  2 3   4
// < text | > text
int	pipe_operators(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{	
		if ((is_operator(split[i]) && split[i + 1]))
		{
			printf("Here1\n");
			if (split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_pipes(split[i]) && split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_rdr(split[i]) && is_operator(split[i + 1]))
				return (printf("syntax error near unexpected token '%s'\n", split[i + 1]), 258);
			else if (is_pipes(split[i]) && is_operator(split[i + 1]))
			{
				if (split[i + 2] == NULL || is_operator(split[i + 2]))
					printf("syntax error near unexpected token '%s'\n", split[i]);
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			}
		}
		i++;
	}
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

int	syntax_checking(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (is_operator(split[i]) == 4)
			return (unsigned_operators(split[i]));
		if ((pipe_operators(split)) == 258)
			return (258);
	}
	return (0);
}
