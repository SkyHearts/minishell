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
	int		i;
	i = -1;
	while (path[++i])
	{
		directory = ft_strjoin(path[i], "/");
		dir_cmd = ft_strjoin(directory, cmd);
		free(directory);
		if (access(dir_cmd, X_OK) == 0)
			return (dir_cmd);
		// free(dir_cmd);
	}
	return (NULL);
}

void	call_cmd(t_env *env_table, t_pipe pipe, char **envp, int index)
{
	int i;
	(void)index;

	i = -1;
	pipe.cmd = find_cmd(env_table->path, pipe.args[0]);
	if (!pipe.cmd)
	{
		free(pipe.cmd);
		error(ERR_CMD);
		exit(1);
	}
	execve(pipe.cmd, pipe.args, envp);
	free(pipe.cmd);
	
}

int	check_command(t_env *env_table, int m)
{
	int i = -1;
	while (++i < 5)
	{
		if (ft_strcmp(env_table->cmdgroups[m].args[0], env_table->functions[i]) == 0)
		{
			env_table->func[i](env_table, env_table->cmdgroups[m].args);
			return 1;
		}
	}
	return 0;
}

void	first_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2])
{
	int ret;
	ret = dup2(files[PIPE_OUT], 1);
	if (ret == -1)
		printf("dup fail");

	close(files[PIPE_IN]);
	close(files[PIPE_OUT]);
	// dup2(files[PIPE_IN], 0);
	if (check_command(env_table, m) == 0)
	{
		call_cmd(env_table, pipe, envp, 0);
	}
}

void	last_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2])
{
	dup2(files[PIPE_IN], 0);
	close(files[PIPE_IN]);
	close(files[PIPE_OUT]);
	// dup2(files[PIPE_OUT], 1);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, 1);
}

void	middle_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2])
{
	dup2(files[PIPE_IN], 0);
	close(files[PIPE_IN]);
	close(files[PIPE_OUT]);
	// dup2(files[PIPE_OUT], 1);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, 1);
}

void	parent(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2])
{
	int ret;
	ret = 	dup2(files[PIPE_IN], 0);
	if (ret == -1)
		printf("dup fail");

	close(files[PIPE_IN]);
	close(files[PIPE_OUT]);
	// dup2(files[PIPE_OUT], 1);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, 1);
}

void	multi_pipe(t_env *env_table, char **envp)
{
	pid_t	pid;
	int		status;
	int		files[2];
	int		m;
 
	m = -1;
	pid = fork();
	
	while (++m < env_table->nos_pipe)
	{
		if (pid == 0)
		{
			if (m == 0)
				first_child(env_table, env_table->cmdgroups[0], m, envp, files);
			else if (m == env_table->nos_pipe - 1)
				last_child(env_table, env_table->cmdgroups[0], m, envp, files);
			else
				middle_child(env_table, env_table->cmdgroups[0], m, envp, files);
		}
		else
			parent(env_table, env_table->cmdgroups[0], m, envp, files);
	}
	waitpid(pid, &status, 0);
}

void one_child(t_env *env_table, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (check_command(env_table, 0) == 0)
			call_cmd(env_table, env_table->cmdgroups[0], envp, 1);
	}
	waitpid(pid, &status, 0);
}

void	ft_pipe(t_env *env_table, char **envp)
{
	if (env_table->nos_pipe > 1)
			multi_pipe(env_table, envp);
	else
		one_child(env_table, envp);
}
