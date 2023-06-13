/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:55 by sulim             #+#    #+#             */
/*   Updated: 2023/06/13 21:28:39 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_cmd(char **path, char *cmd)
{
	char	*directory;
	char	*dir_cmd;

	while (*path)
	{
		directory = ft_strjoin(*path, "/");
		dir_cmd = ft_strjoin(directory, cmd);
		free(directory);
		if (access(dir_cmd, X_OK) == 0)
			return (dir_cmd);
		free(dir_cmd);
		path++;
	}
	return (NULL);
}

void	call_cmd(t_env *env_table, t_pipe pipe, char **envp, int index)
{
	int i;

	i = -1;

	while( env_table->path[++i] != NULL)
	{
		pipe.cmd = find_cmd(&env_table->path[i], *env_table->cmdgroups[index].args);
		if (!pipe.cmd)
		{
			free(pipe.cmd);
			error(ERR_CMD);
			exit(1);
		}
		execve(pipe.cmd, pipe.args, envp);
		free(pipe.cmd);
	}
}

void	parent(t_env *env_table, t_pipe pipe, char **envp, int files[2])
{
	dup2(files[PIPE_OUT], 1);
	close(files[PIPE_IN]);
	dup2(files[PIPE_IN], 0);
	call_cmd(env_table, pipe, envp, 0);
}

void	child(t_env *env_table, t_pipe pipe, char **envp, int files[2])
{
	dup2(files[PIPE_IN], 0);
	close(files[PIPE_OUT]);
	dup2(files[PIPE_OUT], 1);
	call_cmd(env_table, pipe, envp, 1);
}

void	one_pipe(t_env *env_table, char **envp)
{
	pid_t	pid;
	int files[2];

	pid = fork();
	if (pid == 0)
		child(env_table, env_table->pipe[0], envp, files);
	else
	{
		parent(env_table, env_table->pipe[0], envp, files);
	}
}

void	ft_pipe(t_env *env_table, char **envp)
{
	// if (env_table->nos_pipe >= 2)
	// 	multi_pipe(env_table, envp);
	// else
		one_pipe(env_table, envp);
}
