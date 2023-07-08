/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:01:37 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 12:24:48 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == ' ' )
		return (1);
	if (c == '\v' || c == '\f' || c == '\r' )
		return (1);
	return (0);
}

int	isempty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	reduce_white_spaces_3(char *s)
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
		{
			quote_type = s[i];
			s[j++] = s[i++];
			while (s[i] && s[i] != quote_type)
				s[j++] = s[i++];
		}
		if (!ft_isspace(s[i]) || (i > 0 && !ft_isspace(s[i - 1])))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
	while (s[--j] == ' ')
		s[j] = '\0';
}
