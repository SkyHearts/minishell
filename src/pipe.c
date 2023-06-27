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

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

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
	int	status;
	int i;

	i = -1;

	while (++i < env_table->nos_pipe)
	{
		if (waitpid(pid[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				env_table->errnumber = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				if (WTERMSIG(status) == 2)
					env_table->errnumber = 130;
		}
		else
			printf("waitpid error");
	}
}

char	*find_cmd(char **path, char *cmd)
{
	char	*directory;
	char	*dir_cmd;
	int		i;
	i = -1;
	if (!path)
		return (NULL);
	while (path[++i])
	{
		if (cmd[0] != '.')
			directory = ft_strjoin(path[i], "/");
		else
			directory = ft_strdup("");
		dir_cmd = ft_strjoin(directory, cmd);
		// printf("dir_cmd[%s]\n", dir_cmd);
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
	reset_signal();
	pipe.cmd = find_cmd(env_table->path, *pipe.args);
	// printf("pipe.cmd[%s] pipe.args[%s]\n", pipe.cmd, *pipe.args);
	if (!pipe.cmd)
	{
		free(pipe.cmd);
		// error(FAIL_PIPE);
		printf("%s: %s\n", pipe.args[0], "No such file or directory");
		exit(127);
	}
	execve(pipe.cmd, pipe.args, envp);
	free(pipe.cmd);
	exit(0);
}

int	check_command(t_env *env_table, int m)
{
	int i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(env_table->cmdgroups[m].args[0], env_table->functions[i]) == 0)
		{
			env_table->func[i](env_table, env_table->cmdgroups[m].args);
			exit(0);
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
				// printf("first_child %d\n", m);
				first_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
			else if (m == env_table->nos_pipe - 1)
			{
				// printf("last_child %d\n", m);
				last_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
			else
			{
				// printf("middle_child %d\n", m);
				middle_child(env_table, env_table->cmdgroups[m], m, envp, files);
			}
		}
		else
		{
			// printf("parent close fd %d\n", m);
			parent(env_table->nos_pipe, m, files);
		}
	}
}

int	run_one_command(t_env *env_table, int i)
{
	env_table->func[i](env_table, env_table->cmdgroups[0].args);
	return (0);
}

int	run_builtins(t_env *env_table, int m)
{
	int i;

	i = -1;
	if (!ft_strcmp(env_table->cmdgroups[m].args[0], "cd"))
		i = 1;
	else if (!ft_strcmp(env_table->cmdgroups[m].args[0], "export"))
		i = 3;
	else if (!ft_strcmp(env_table->cmdgroups[m].args[0], "unset"))
		i = 4;
	else if (!ft_strcmp(env_table->cmdgroups[m].args[0], "exit"))
		i = 6;
	if (i != -1)
	{
		return (run_one_command(env_table, i));//in out operations
	}
	return (i);
}

int one_child(t_env *env_table, char **envp, int *pid)
{
	int ret;

	ret = -1;
	if (env_table->cmdgroups[0].args != NULL)
		ret = run_builtins(env_table, 0);
	if (ret != -1)
		return (1);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		if (check_command(env_table, 0) == 0)
			call_cmd(env_table, env_table->cmdgroups[0], envp);
	}
	return (ret);
}

void	ft_pipe(t_env *env_table, char **envp)
{
	pid_t	*pid;
	int ret;

	ret = -1;
	signal(SIGINT, sig_handler_nl);
	env_table->path = extract_path(env_table, env_table->env);
	// print_darray(env_table->path);
	pid = ft_calloc(env_table->nos_pipe, sizeof(int));
	if (env_table->nos_pipe > 1)
		multi_pipe(env_table, envp, pid);
	else
		ret = one_child(env_table, env_table->env, pid);
	if (ret == -1)
		wait_pid(env_table, pid);
	free(pid);
}
