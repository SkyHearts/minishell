/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:54:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/27 11:03:37 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_env_var(t_env *env_table, char *argv)
{
	char	**tmp_table;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	while (env_table->env[size] != NULL)
		size++;
	tmp_table = (char **) malloc(sizeof(char *) * (size));
	i = 0;
	while (env_table->env[j] != NULL && j < size)
	{
		if (ft_strncmp(env_table->env[j], argv, ft_strlen(argv)))
		{
			tmp_table[i] = ft_strdup(env_table->env[j]);
			i++;
			j++;
		}
		else
			j++;
	}
	tmp_table[i] = NULL;
	free_doublearray(env_table->env);
	env_table->env = tmp_table;
}

void	update_env_unset(t_env *env_table, char *argv)
{
	int		i;
	int		j;
	int		var_found;

	i = -1;
	j = -1;
	var_found = 0;
	while (env_table->env[++i] != NULL)
	{
		if (!ft_strncmp(env_table->env[i], argv, ft_strlen(argv)))
		{
			var_found = 1;
			break ;
		}
	}
	if (var_found == 1)
		delete_env_var(env_table, argv);
}

void	ft_unset(t_env *env_table, char **argv)
{
	int		i;
	int		j;

	j = -1;
	while (argv[++j])
	{
		if (!ft_isalpha(argv[j][0]))
		{
			printf("unset: `%s': not a valid identifier argument\n", argv[j]);
			return ;
		}
		i = 0;
		while (argv[j][++i])
		{
			if (!ft_isalnum(argv[j][i]))
			{
				printf("unset: `%s': not a valid identifier argument\n", argv[j]);
				return ;
			}
		}
		update_env_unset(env_table, argv[j]);
	}
}