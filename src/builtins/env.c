/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:56:49 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 11:29:50 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_env *env_table, char **str)
{
	int	i;

	(void)str;
	i = 0;
	while (env_table->env[i])
	{
		ft_printf("%s\n", env_table->env[i]);
		i++;
	}
	return (0);
}
