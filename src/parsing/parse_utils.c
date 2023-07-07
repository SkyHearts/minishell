/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:41 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 10:33:07 by sulim            ###   ########.fr       */
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

int	unsigned_operators(char **split, int i)
{
	int strike;
	int j;
	j = 0;
	strike = -1;

	while (split[i][j])
	{
		if (is_rdr(split[i]))
		{
			strike++;
			j++;
			if (strike > 0)
			{
				printf("syntax error near unexpected token '%s'\n", split[i]);
				return (258);
			}
		}
		else
			break;
	}

	printf("opp3\n");
	(void) i;
	if (!ft_strncmp(split[0], "<<<", 3) && split[1] != NULL && (split[2] != NULL && !ft_strcmp(split[2], "cat")))
		printf("%s\n", split[1]);
	// else if (!ft_strcmp(split[i+1], "|>"))
	// {
	// 	if(split[i+1] == NULL)
	// 		printf("syntax error near unexpected token 'newline'\n");
	// 	else
	// 		exit(1);
	// }
	else if (split[i][j] == '>' || split[i][j] == '<' || split[i][j] == '|')
	{
		// pipe_operators();
		printf("syntax error near unexpected token '%s'\n", split[i]);
	}
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
		printf("opp5, %s, %s\n", split[i], split[i+2]);
		// if ((is_operator(split[i]) && split[i + 1]))
		// {
			if (split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_pipes(split[i]) && split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_rdr(split[i]) && is_operator(split[i + 1]))
				return (printf("syntax error near unexpected token '%s'\n", split[i + 1]), 258);
			else if (is_pipes(split[i]) && is_operator(split[i + 2]) == 4)
			{
				printf("opp6\n");
				return (printf("syntax error near unexpected token '%s'\n", split[i + 3]), 258);
			}
			else if (split[i + 2] == NULL || is_operator(split[i + 2]))
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
		// }
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

void ft_correct_space(char **split)
{
	// int strike;
	int i;
	int j;
	j = 0;
	i = 0;
	// strike = -1;
	printf("before: %s", split[0]);
	while (split[i][j])
	{
		if (split[i][j] == split[i][j+1])
		{
			split[i][j] = split[i][j];
			split[i][j+1] = split[i][j+1];
			i+=1;
			j = 0;
		}
		else
			break;
	}
}

int	syntax_checking(char **split)
{
	int	i;
	i = -1;

	// split = ft_correctspace(split);
	printf("ans: %s", split[0]);
	while (split[++i])
	{
		if (!is_operator(split[i]))
		{
			printf ("what is this? %s \n ", split[i]);
			return (unsigned_operators(split, i));
		}
		// if (is_operator(split[i]) == 3)
		// {
		// 	pipe_operators(split);
		// 	return (258);
		// }
		// if ((pipe_operators(split)) == 258)
		// 	return (258);
	}
	return (0);
}
