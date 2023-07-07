/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:54:32 by sulim             #+#    #+#             */
/*   Updated: 2023/07/07 15:41:28 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_dup(int m, int fd1, int fd2)
{
	int ret;
	(void) m;
	// printf("[%d]\n", m);
	ret = dup2(fd1, fd2);

	if (ret == -1)
		error(FAIL_DUP);
}

char	*find_cmd(char **path, char *cmd)
{
	char	*directory;
	char	*dir_cmd;
	int		i;
	i = -1;
	while (path[++i])
	{
		directory = ft_strjoin(path[i], "/");
		dir_cmd = ft_strjoin(directory, cmd);
		free(directory);
		if (access(dir_cmd, X_OK) == 0)
			return (dir_cmd);
		free(dir_cmd);
	}
	return (NULL);
}

void	call_cmd(t_env *env_table, t_pipe pipe, char **envp, int m)
{
	int i;

	i = -1;
	if (env_table->cmdgroups[m].args == NULL)
		return ;
	pipe.cmd = find_cmd(env_table->path, *pipe.args);
	// printf("%s %s\n", pipe.cmd, *pipe.args);
	if (!pipe.cmd)
	{
		free(pipe.cmd);
		error(FAIL_PIPE);
		exit(1);
	}
	execve(pipe.cmd, pipe.args, envp);
	free(pipe.cmd);
}

int	check_command(t_env *env_table, int m)
{
	int i = -1;
	if (env_table->cmdgroups[m].args == NULL)
		exit(0);
	while (++i < 7)
	{
		if (ft_strcmp(env_table->cmdgroups[m].args[0], env_table->functions[i]) == 0)
		{
			env_table->func[i](env_table, env_table->cmdgroups[m].args);
			exit(0);
		}
	}
	return 0;
}