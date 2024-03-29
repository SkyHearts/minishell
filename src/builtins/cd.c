/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:52:52 by jyim              #+#    #+#             */
/*   Updated: 2023/07/10 12:05:45 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Return Home directory from env or NULL if var don't exist  */
char	*gethome(char **env_table)
{
	int		i;

	i = 0;
	while (env_table[i])
	{
		if (!ft_strncmp(env_table[i], "HOME=", 5))
			return (ft_substr(env_table[i], 5, ft_strlen(env_table[i]) - 5));
		i++;
	}
	return (NULL);
}

/* Only updates PWD and OLDPWD if env var still exist */
void	update_pwd(t_env *env_table, char *oldpwd)
{
	char	**env;
	char	*cwd;
	int		i;

	i = -1;
	env = env_table->env;
	cwd = getcwd(NULL, 0);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", cwd);
		}
		else if (!ft_strncmp(env[i], "OLDPWD=", 4))
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
	}
	free(cwd);
	free(oldpwd);
}

int	ft_cd(t_env *env_table, char **str)
{
	char	*cwd;
	char	*home;

	cwd = getcwd(NULL, 0);
	home = gethome(env_table->env);
	if (str[1] == NULL || !ft_strcmp(str[1], "~"))
	{
		if (!home)
			return (free(cwd), ft_printf("cd: HOME not set\n"), 1);
		chdir(home);
	}
	else
	{
		if (chdir(str[1]))
		{
			perror("cd: ");
			return (free(home), free(cwd), errno);
		}
	}
	update_pwd(env_table, cwd);
	free(home);
	return (0);
}
