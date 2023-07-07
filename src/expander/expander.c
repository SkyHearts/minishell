/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:18 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 14:32:35 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmp_s(char s, char *op_list)
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
	int		j;
	int		i;
	char	cur_operator;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(s))
	{
		if (cmp_s(s[i], OPERATORS) && s[i] != cur_operator)
		{
			cur_operator = s[i];
			if (i != 0)
				output[j++] = ' ';
			while (s[i] == cur_operator)
				output[j++] = s[i++];
			if (i < (int)ft_strlen(s) && s[i] != ' ' && !cmp_s(s[i], OPERATORS))
				output[j++] = ' ';
		}
		else
			output[j++] = s[i++];
		cur_operator = 0;
	}	
	return (output[j] = '\0', free(s), ft_strdup(output));
}
