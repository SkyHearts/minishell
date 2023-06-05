/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:52:31 by jyim              #+#    #+#             */
/*   Updated: 2023/06/05 18:46:04 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	char_separator(char str, char c)
{
	if (str == c || str == '\0')
		return (1);
	return (0);
}

/* count how many argument there is for malloc */
static int	arg_count_quoted(char *input, char c)
{
	int		i;
	int		argc;
	char	quote_type;

	i = -1;
	argc = 0;
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
		}
		if (char_separator(input[i + 1], c) == 1
			&& char_separator(input[i], c) == 0)
			argc++;
	}
	printf("argc = %d\n", argc);
	return (argc);
}

/* iterate through input and stop only when end of string or end of quote */
static void	process_quotes(char *input, int *i)
{
	char	quote_type;

	quote_type = input[(*i)++];
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (input[*i] == quote_type && input[*i + 1] != '\0')
		(*i)++;
}

/* Allocated memory, save one line */
static char	**split_allocation(int size)
{
	char	**splitted;

	splitted = (char **)malloc(sizeof(char *) * (size + 1));
	return (splitted);
}

/* Splite arguments, check guide */
char	**ft_split_quoted(char *input, char delim)
{
	char	**splitted;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	splitted = split_allocation(arg_count_quoted(input, delim));
	if (!splitted)
		return (NULL);
	while (i <= ft_strlen(input))
	{
		if (if_quotes(input[i]) && input[i + 1])
			process_quotes(input, &i);
		else if (input[i] == delim || input[i] == '\0')
		{
			splitted[k++] = ft_substr(input, j, i - j);
			j = ++i;
		}
		else
			i++;
	}
	splitted[k] = NULL;
	return (splitted);
}
