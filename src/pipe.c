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

void	ft_dup(int m, int fd1, int fd2)
{
	int ret;
	printf("[%d]\n", m);
	ret = dup2(fd1, fd2);

	if (ret == -1)
		error(FAIL_DUP);
}

void	wait_pid(t_env *env_table, int *pid)
{
	int		status;
	int i;

	i = -1;

	while (++i < env_table->nos_pipe)
	{
		printf("nos pipe [%d]\n", env_table->nos_pipe);
		printf("enter waitpid [%d]\n", i);
		waitpid(pid[i], &status, 0);
		printf("pass wait\n");
	}
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

void	call_cmd(t_env *env_table, t_pipe pipe, char **envp)
{
	int i;

	i = -1;
	pipe.cmd = find_cmd(env_table->path, *pipe.args);
	// printf("%s %s\n", pipe.cmd, *pipe.args);
	if (!pipe.cmd)
	{
		free(pipe.cmd);
		error(FAIL_PIPE);
		exit(1);
	}
	// printf("here \n");
	execve(pipe.cmd, pipe.args, envp);
	// printf("pass execve\n");
	free(pipe.cmd);
}

int	check_command(t_env *env_table, int m)
{
	int i = -1;
	while (++i < 5)
	{
		if (ft_strcmp(env_table->cmdgroups[m].args[0], env_table->functions[i]) == 0)
		{
			// printf("pass\n");
			env_table->func[i](env_table, env_table->cmdgroups[m].args);
			exit(0);
			// return (1);
		}
	}
	return (0);
}

void	last_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2][2])
{
	ft_dup(m, files[1][0], STDIN_FILENO);
	close(files[0][0]);
	close(files[0][1]);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp);
}

void	middle_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2][2])
{
	ft_dup(m, files[0][1], STDOUT_FILENO);
	ft_dup(m ,files[1][0], STDIN_FILENO);
	close(files[0][0]);
	close(files[0][1]);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp);
}

void	first_child(t_env *env_table, t_pipe pipe, int m, char **envp, int files[2][2])
{
	ft_dup(m, files[0][1], STDOUT_FILENO);
	close(files[0][0]);
	close(files[0][1]);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp);
}

void	parent(int num_pipe, int m, int files[2][2])
{
	if (m != 0)
	{
		// middle, last
		close(files[1][0]);
	}
	if (m != num_pipe - 1)
	{
		// first cmd, middle cmd
		files[1][0] = files[0][0];
	}
	// all
	close(files[0][1]);
	if (m == num_pipe - 1)
	{
		// last
		close(files[0][0]);
	}
}

void	multi_pipe(t_env *env_table, char **envp, int *pid)
{
	int		files[2][2];
	int		m;
 
	m = -1;
	while (++m < env_table->nos_pipe)
	{
		// pipe(files[0]);
		if (m < env_table->nos_pipe && pipe(files[0]) == -1)
		{
			printf("Bad pipe [%d]", m);
			exit(1);
		}
		pid[m] = fork();
		if (pid[m] == 0)
		{
			if (m == 0)
			{
				printf("first_child %d\n", m);
				first_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
			else if (m == env_table->nos_pipe - 1)
			{
				printf("last_child %d\n", m);
				last_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
			else
			{
				printf("middle_child %d\n", m);
				middle_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
		}
		else
		{
			printf("parent close fd %d\n", m);
			parent(env_table->nos_pipe, m, files);
		}
	}
}

void one_child(t_env *env_table, char **envp, int *pid)
{
	pid[0] = fork();
	if (pid[0] == 0)
	{
		if (check_command(env_table, 0) == 0)
			call_cmd(env_table, env_table->cmdgroups[0], envp);
	}
}

void	ft_pipe(t_env *env_table, char **envp)
{
	pid_t	*pid;

	pid = ft_calloc(env_table->nos_pipe, sizeof(int));
	if (env_table->nos_pipe > 1)
		multi_pipe(env_table, envp, pid);
	else
		one_child(env_table, envp, pid);

	wait_pid(env_table, pid);
	free(pid);
}
