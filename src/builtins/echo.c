/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:50:43 by jyim              #+#    #+#             */
/*   Updated: 2023/06/29 14:48:53 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_start(char **str, int start)
{
	while (str[start])
	{
		printf("%s", str[start]);
		if (str[start + 1])
			printf(" ");
		start++;
	}
}

int	ft_echo(t_env *env_table, char **str)
{
	int	i;
	int	n_option;

	(void)env_table;
	i = 0;
	n_option = 0;
	if (!ft_strncmp(str[1], "-", 1))
	{
		while (str[1][++i])
		{
			if (str[1][i] == 'n')
				n_option = 1;
			else
				n_option = 0;
		}
	}
	if (!n_option)
	{
		print_start(str, 1);
		printf("\n");
	}
	else
		print_start(str, 2);
	return (0);
}
