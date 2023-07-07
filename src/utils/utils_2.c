/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:31:30 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 18:01:29 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_pipes(char *splitted)
{
	if (!ft_strcmp(splitted, "|"))
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "|"))
		return (3);
	return (0);
}

int	is_rdr(char *splitted)
{
	if (!ft_strcmp(splitted, "<"))
		return (1);
	if (!ft_strcmp(splitted, ">"))
		return (2);
	if (!ft_strcmp(splitted, "<<"))
		return (3);
	if (!ft_strcmp(splitted, ">>"))
		return (4);
	return (0);
}

int	is_op_then_cmp(char *splitted)
{
	if (splitted[0] == '|' || splitted[0] == '<' || splitted[0] == '>')
	{
		if (is_rdr(splitted) || is_pipes(splitted))
			return (1);
		else
			return (0);
	}
	return (-1);
}

char	*ft_strcat(char *s1, const char *s2)
{
	char	*dest;

	dest = s1;
	while (*s1)
		s1++;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (dest);
}
