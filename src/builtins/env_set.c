/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:55:18 by jyim              #+#    #+#             */
/*   Updated: 2023/06/29 14:52:30 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
check if environment varaible exist
if environment variable exist don't exist, exit function
malloc 1 less memory from env_table
copy all environment variable without argv
 */
void	ft_unset(t_env *env_table, char **argv)
{
	int		i;
	int		j;
	int		found;
	char	**tmp_table;

	i = -1;
	j = -1;
	found = 0;
	while (env_table->env[++i] != NULL)
		if (!ft_strncmp(env_table->env[i], argv[1], ft_strlen(argv[1]) + 1))
			found = 1;
	if (!found)
		return ;
	tmp_table = (char **) malloc(sizeof(char *) * (i));
	i = -1;
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

/* check if any arguments have '=' */
/*  go to '=' in the argument */
/* return error msg if no char before '=', space and tab not considered char */
void	ft_export(t_env *env_table, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (!ft_strchr(argv[j], '='))
		j++;

	while (argv[j][i] != '=')
		i++;

	if (argv[j][i - 1] == ' ' || argv[j][i - 1] != '\t')
		return ;
	while (i != 0 && (argv[j][i - 1] != ' ' || argv[j][i - 1] != '\t'))
		i--;
	dup_env_extra(env_table, argv[j] + i);
}

void	ft_env(t_env *env_table, char **str)
{
	int	i;

	(void)str;
	i = 0;
	while (env_table->env[i])
	{
		printf("%s\n", env_table->env[i]);
		i++;
	}
}

void	ft_pwd(t_env *env_table, char **str)
{
	char	*cwd;

	(void)str;
	(void)env_table;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_exit(t_env *env_table, char **str)
{
	(void)env_table;
	(void)str;
	exit(0);
}
