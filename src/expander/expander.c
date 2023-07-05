/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:18 by jyim              #+#    #+#             */
/*   Updated: 2023/07/05 18:50:55 by jyim             ###   ########.fr       */
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
// Copy the original string up to the insertion position
// Insert the space
// Copy the remaining characters from the original string
// Add the null terminator
// Free the original string
// Return the modified string
// Failed to allocate memory, return the original string
 */
char	*add_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (new_str != NULL)
	{
		ft_strncpy(new_str, str, pos);
		new_str[pos] = ' ';
		ft_strncpy(new_str + pos + 1, str + pos, len - pos);
		new_str[len + 1] = '\0';
		free(str);
		return (new_str);
	}
	else
		return (str);
}

/* 
// Copy the original string up to the remove space position
// Copy the remaining characters from the original string
// Add the null terminator
// Free the original string
// Return the modified string
// Failed to allocate memory, return the original string
 */
char	*reduce_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len));
	if (new_str != NULL)
	{
		ft_strncpy(new_str, str, pos);
		ft_strncpy(new_str + pos, str + pos + 1, len - pos - 1);
		new_str[len - 1] = '\0';
		free(str);
		return (new_str);
	}
	else
		return (str);
}

char	*expand_str(char *s, int i)
{
	if (s[i + 1] != ' ' && !ft_char_cmp_str(s[i + 1], OPERATORS)
		&& !if_quotes(s[i + 1]) && s[i + 1])
		s = add_space(s, ft_strlen(s), i + 1);
	if (i > 0)
	{
		if (if_quotes(s[i - 1]) && s[i] == '|')
			s = add_space(s, ft_strlen(s), i);
		else if (if_quotes(s[i - 1]) && ft_char_cmp_str(s[i - 1], "\"'"))
			s = add_space(s, ft_strlen(s), i);
		else if (s[i - 1] != ' ' && !ft_char_cmp_str(s[i - 1], OPERATORS)
			&& !if_quotes(s[i - 1]))
			s = add_space(s, ft_strlen(s), i);
	}
	return (s);
}

/* 
Function adds whitespace to locations with OPERATORS and QUOTES using the
expand_str function.
Example : echo hello|wc -> echo hello | wc
 */
char	*expand_operators(char *s)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = -1;
	while (s[i])
	{
		if (if_quotes(s[i]))
		{
			quote_type = s[i++];
			while (s[i] && s[i] != quote_type)
				i++;
		}
		else if (s[i] == PIPE)
			s = expand_str(s, i);
		else if (s[i] == REDIRECT_LEFT)
			s = expand_str(s, i);
		else if (s[i] == REDIRECT_RIGHT)
			s = expand_str(s, i);
		i++;
	}
	return (s);
}
