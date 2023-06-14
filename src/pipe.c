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

int	check_command(t_env *env_table, char *cmd, int m)
{
	// char *function[] = { "echo", "cd", "pwd", "export" "unset" "env" "exit"};
	// int i = -1;

	// while (function[++i] != NULL)
	// {
	// 	if (cmd == function[i])
	// 		exit(env_table->func[i](env_table));
	// }

	if (ft_strcmp(cmd, "echo") == 0)
	{
		ft_echo(env_table->cmdgroups[m].args);
		return 1;
	}
	return 0;
}

void	parent(t_env *env_table, t_pipe pipe, char *cmd, int m, char **envp, int files[2])
{
	dup2(files[PIPE_OUT], 1);
	close(files[PIPE_IN]);
	dup2(files[PIPE_IN], 0);
	if (check_command(env_table, cmd, m) == 0)
		call_cmd(env_table, pipe, envp, 0);
}

void	child(t_env *env_table, t_pipe pipe, char *cmd, int m, char **envp, int files[2])
{
	dup2(files[PIPE_IN], 0);
	close(files[PIPE_OUT]);
	dup2(files[PIPE_OUT], 1);
	if (check_command(env_table, cmd, m) == 0)
		call_cmd(env_table, pipe, envp, 1);
}

void	one_pipe(t_env *env_table, char *cmd, int m, char **envp)
{
	pid_t	pid;
	int files[2];

	pid = fork();
	if (pid == 0)
		child(env_table, env_table->pipe[0], cmd, m, envp, files);
	else
		parent(env_table, env_table->pipe[0], cmd, m, envp, files);
}

void	ft_pipe(t_env *env_table, char **envp)
{
	int m = -1;
	while (++m < env_table->nos_pipe)
	{
		int k = -1;
		while (env_table->cmdgroups[m].args[++k])
			one_pipe(env_table, env_table->cmdgroups[m].args[k], m, envp);
	}
	// if (env_table->nos_pipe >= 2)
	// 	multi_pipe(env_table, envp);
	// else
		// one_pipe(env_table, envp);
}
