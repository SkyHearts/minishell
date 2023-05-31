/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:37:53 by jyim              #+#    #+#             */
/*   Updated: 2023/05/06 15:06:21 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**dup_env(char **env)
{
	int		i;
	char	**tmp_table;
	i = 0;
	while (env[i] != NULL)
		i++;
	tmp_table = (char **) malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i] != NULL)
	{
		tmp_table[i] = ft_strdup(env[i]);
		i++;
	}
	tmp_table[i] = NULL;
	return (tmp_table);
}

char	**extract_path(char **env_table)
{
	int		i;
	char	**path_split;

	i = 0;
	while(env_table[i])
	{
		if (!ft_strncmp(env_table[i], "PATH=", 5))
			path_split = ft_split(env_table[i] + 5, ':');
		i++;
	}
	return (path_split);
}

void	show_env(char **env_table)
{
	int i = 0;

	while (env_table[i])
	{
		printf("%s\n", env_table[i]);
		i++;
	}
}