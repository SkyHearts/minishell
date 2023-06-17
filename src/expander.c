/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:18 by jyim              #+#    #+#             */
/*   Updated: 2023/06/14 15:54:04 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_char_cmp_str(char s, char *op_list)
{
	int i;

	i = 0;
	while (op_list[i])
	{
		if (s == op_list[i])
			return (1);
		i++;
	}
	return (0);
}

char	*add_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (new_str != NULL)
	{
		// Copy the original string up to the insertion position
		ft_strncpy(new_str, str, pos);
		// Insert the space
		new_str[pos] = ' ';
		// Copy the remaining characters from the original string
		ft_strncpy(new_str + pos + 1, str + pos, len - pos);
		// Add the null terminator
		new_str[len + 1] = '\0';
		// Free the original string
		free(str);
		// Return the modified string
		return (new_str);
	}
	else
		// Failed to allocate memory, return the original string
		return (str);
}

char	*reduce_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len));
	if (new_str != NULL)
	{
		// Copy the original string up to the remove space position
		ft_strncpy(new_str, str, pos);
		// Copy the remaining characters from the original string
		ft_strncpy(new_str + pos, str + pos + 1, len - pos - 1);
		// Add the null terminator
		new_str[len - 1] = '\0';
		// Free the original string
		free(str);
		// Return the modified string
		return (new_str);
	}
	else
		// Failed to allocate memory, return the original string
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

// int	ft_is_double_operator(char *s, int i)
// {
// 	if(s[i] == ' ')
// 		if (ft_str_cmp_str(s[i - 1], OPERATORS) && ft_str_cmp_str(s[i + 1], OPERATORS))
// 			return (1);
// 	return (0);
// }

// char	*reduce_double_operators(char *s)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (ft_is_double_operator(s, i))
// 			s = reduce_space(s, ft_strlen(s), i);
// 		i++;
// 	}
// 	return (s);
// }