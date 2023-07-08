/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:55:08 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 11:32:31 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_env_cont(t_env *env_table, char *new_env, int j)
{
	int	i;

	i = -1;
	while (env_table->env[++i] != NULL)
	{
		if (!ft_strncmp(env_table->env[i], new_env, j + 1))
			break ;
	}
	free(env_table->env[i]);
	env_table->env[i] = new_env;
}

void	new_env_var(t_env *env_table, char *new_env)
{
	char	**tmp_table;
	int		i;

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
	tmp_table[i] = new_env;
	tmp_table[i + 1] = NULL;
	free_doublearray(env_table->env);
	env_table->env = tmp_table;
}

void	update_env_export(t_env *env_table, char *new_env)
{
	int		i;
	int		j;
	int		dup_found;

	i = -1;
	j = -1;
	dup_found = 0;
	while (new_env[++j])
		if (new_env[j] == '=')
			break ;
	while (env_table->env[++i] != NULL)
		if (!ft_strncmp(env_table->env[i], new_env, j + 1))
			dup_found = 1;
	if (dup_found == 1)
		update_env_cont(env_table, new_env, j);
	else
		new_env_var(env_table, new_env);
}

/* check if any arguments have '=' and only run if variable is correct */
int	ft_export(t_env *env_table, char **argv)
{
	int		i;
	int		j;
	char	*env_cont;

	j = 0;
	while (argv[j])
	{
		if (ft_strchr(argv[j], '='))
		{
			i = 0;
			while (argv[j][++i])
			{
				if (!ft_isalnum(argv[j][i]) && !ft_isalpha(argv[j][0]))
				{
					ft_printf("env: %s: Invalid argument\n", argv[j]);
					return (1);
				}
			}
			env_cont = ft_substr(argv[j], 0, ft_strlen(argv[j]));
			update_env_export(env_table, env_cont);
		}
		j++;
	}
	return (0);
}
