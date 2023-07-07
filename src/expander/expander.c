/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:18 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 15:07:35 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_char_cmp_str(char s, char *op_list)
{
	int	i;

	i = 0;
	while (op_list[i])
	{
		if (s == op_list[i])
			return (1);
		i++;
	}
	return (0);
}

/* 
Function adds whitespace to locations with OPERATORS and QUOTES using the
expand_str function.
Example : echo hello|wc -> echo hello | wc
 */
char	*expand_operators(char *s)
{
	char	output[1000];
	int		size;
	int		j;
	int		i;
	char	cur_operator;

	i = 0;
	j = 0;
	size = ft_strlen(s);
	cur_operator = 0;
	while (i < size)
	{
		if (ft_char_cmp_str(s[i], OPERATORS) && s[i] != cur_operator)
		{
			cur_operator = s[i];
			if (i != 0)
				output[j++] = ' ';
			while (s[i] == cur_operator)
				output[j++] = s[i++];
			if (i < size && s[i] != ' ' && !ft_char_cmp_str(s[i], OPERATORS))
				output[j++] = ' ';
		}
		else
			output[j++] = s[i++];
		cur_operator = 0;
	}
	if (output[j - 1] == ' ')
		output[j - 1] = '\0';
	output[j] = '\0';
	free(s);
	return (ft_strdup(output));
}
