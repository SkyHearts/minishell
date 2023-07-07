/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:45:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/29 14:41:30 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error(char *err)
{
	perror(err);
	exit(1);
}

int	if_quotes(char input)
{
	if (input == SINGLE_QUOTE || input == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	ft_isalpha_equal(int c)
{
	if ((c >= 65 && c <= 90) || c == '=')
		return (c);
	else if ((c >= 97 && c <= 122) || c == '=')
		return (c);
	else
		return (0);
}

int	ft_isalnum_q(int c)
{
	if ((c >= 65 && c <= 90) || c == '?')
		return (c);
	else if (c >= 97 && c <= 122)
		return (c);
	else if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}

int	has_pipes(char **splitted)
{
	int	i;
	int	pipes;

	i = -1;
	pipes = 1;
	while (splitted[++i])
	{
		if (!ft_strcmp(splitted[i], "|"))
			pipes++;
	}
	return (pipes);
}
