/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:55:08 by jyim              #+#    #+#             */
/*   Updated: 2023/06/17 11:55:23 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup_env_extra(t_env *env_table, char *new_env)
{
	int		i;
	char	**tmp_table;
	i = 0;
	while (env_table->env[i] != NULL)
		i++;
	tmp_table = (char **) malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env_table->env[i] != NULL)
	{
		tmp_table[i] = ft_strdup(env_table->env[i]);
		i++;
	}
	tmp_table[i] = ft_strdup(new_env);
	tmp_table[i + 1] = NULL;
	fre_doublearray(env_table->env);
	env_table->env = tmp_table;
}

void	ft_export(t_env *env_table, char **argv)
{
	int i;
	int	j;
	i = 0;
	j = 0;

	/* check if any arguments have '=' */
	while (!ft_strchr(argv[j], '='))
		j++;
	/*  go to '=' in the argument */
	while (argv[j][i] != '=')
		i++;
	/* return error msg if no char before '=', space and tab not considered char */
	if (argv[j][i - 1] == ' ' || argv[j][i - 1] != '\t')
		return ;
	while (i != 0 && (argv[j][i - 1] != ' ' || argv[j][i - 1] != '\t'))
		i--;
	dup_env_extra(env_table, argv[j] + i);
}
