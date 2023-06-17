/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:54:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/17 11:55:03 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset(t_env *env_table, char **argv)
{
	int		i;
	int		j;
	int		found;
	char	**tmp_table;

	i = -1;
	j = -1;
	found = 0;
	/* check if environment varaible exist */
	while (env_table->env[++i] != NULL)
		if (!ft_strncmp(env_table->env[i], argv[1], ft_strlen(argv[1]) + 1))
			found = 1;
	/* if environment variable exist don't exist, exit function */		
	if (!found)
		return ;
	/* malloc 1 less memory from env_table */	
	tmp_table = (char **) malloc(sizeof(char *) * (i));
	i = -1;
	/* copy all environment variable without argv */	
	while (env_table->env[++i] != NULL)
	{
		if (!ft_strncmp(env_table->env[i], argv, ft_strlen(argv[1]) + 1))
			i++;
		tmp_table[++j] = ft_strdup(env_table->env[i]);
	}
	tmp_table[++j] = NULL;
	free(env_table->env);
	env_table->env = tmp_table;
}