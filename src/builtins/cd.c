/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:52:52 by jyim              #+#    #+#             */
/*   Updated: 2023/06/17 11:57:30 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* // ======================================================================
void	free_doublearray(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

void	print_darray(char **array)
{
	int	i;

	i = 0;
	printf("--------Double ARRAY--------\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("----------------------------\n");
}

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
// ======================================================================
 */
char	*join_path(char const *s1, char const *s2)
{
	size_t	join_len;
	size_t	i;
	size_t	j;
	char	*strjoin;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	join_len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (join_len) + 2);
	if (!strjoin)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	strjoin[i++] = '/';
	j = 0;
	while (s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}

char	*gethome(char **env_table)
{
	int		i;
	char	**path_split;

	i = 0;
	while (env_table[i])
	{
		if (!ft_strncmp(env_table[i], "HOME=", 5))
			return (ft_substr(env_table[i], 5, ft_strlen(env_table[i]) - 5));
		i++;
	}
	return (NULL);
}

char	*directory_above(char *cwd)
{
	int		i;
	char	*ret;

	i = ft_strlen(cwd);
	while (cwd[i] != '/')
		i--;
	ret = ft_substr(cwd, 0, i);
	return (ret);
}

void	change_dir(t_env *env_table, char **dir)
{
	char	*u_cwd;
	char	*cwd;
	char	*path;
	int		i;

	i = -1;
	while (dir[++i])
	{
		cwd = getcwd(NULL, 0);
		if (!ft_strcmp(dir[i], ".."))
		{
			u_cwd = directory_above(cwd);
			if (chdir(u_cwd))
				perror("cd: ");
			free(u_cwd);
		}
		else
		{
			path = join_path(cwd, dir[i]);
			if (chdir(path))
				perror("cd: ");
			free(path);
		}
		free (cwd);
	}
}

void	cd_free(char **dir, char *home)
{
	free_doublearray(dir);
	free(home);
}

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
	print_darray(env);
}

void	ft_cd(t_env *env_table, char **str)
{
	char	**dir;
	char	*cwd;
	char	*home;

	cwd = getcwd(NULL, 0);
	home = gethome(env_table->env);
	if (str[1] == NULL)
		chdir(home);
	else if (str[1][0] != '/')
	{
		dir = ft_split(str[1], '/');
		change_dir(env_table, dir);
	}
	else
		if (chdir(str[1]))
			perror("cd: ");
	update_pwd(env_table, cwd);
	cd_free(dir, home);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_env	env_table;
// 	char	*s[] = {"cd", "/Users/jyim/Desktop/pds"};

// 	env_table.env = dup_env(env);
// 	ft_cd(&env_table, s);
// }