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

void openfile(int index, int rdrfiles[2], char **hdoc, t_rdrinfo rdrinfo)
{
	(void) hdoc;
	(void)	index;

	if (rdrinfo.rdr_type == IN || rdrinfo.rdr_type == HEREDOC)
	{
		if (rdrfiles[0] != -1)
			close(rdrfiles[0]);
		if (rdrinfo.rdr_type == IN)
			rdrfiles[0] = open(rdrinfo.rdr_str, O_RDONLY);
		// else if (rdrinfo.rdr_type == HEREDOC)
		// 	rdrfiles[0] = 
		if (rdrfiles[0] < 0)
			error(ERR_FILE);
	}
	else if (rdrinfo.rdr_type == OUT || rdrinfo.rdr_type == APPEND)
	{
		if (rdrfiles[1] != -1)
			close (rdrfiles[1]);
		if (rdrinfo.rdr_type == OUT)
			rdrfiles[1] = open(rdrinfo.rdr_str, O_TRUNC | O_CREAT | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
		else if (rdrinfo.rdr_type == APPEND)
			rdrfiles[1] = open(rdrinfo.rdr_str, O_APPEND | O_CREAT | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
		if (rdrfiles[1] < 0)
			error(ERR_FILE);
	}
}

void check_rdr(int index, char **hdoc, t_pipe pipe, int rdrfiles[2])
{
	int count;

	rdrfiles[0] = -1;
	rdrfiles[1] = -1;
	count = -1;
	while (count++ < pipe.rdr_count)
		openfile(index, rdrfiles, hdoc, pipe.rdr_info[count]);
	if (rdrfiles[0] != -1)
		ft_dup(index, rdrfiles[0], STDIN_FILENO);
	if (rdrfiles[1] != -1)
		ft_dup(index, rdrfiles[1], STDOUT_FILENO);
	close(rdrfiles[0]);
	close(rdrfiles[1]);
}

int	run_one_command(t_env *env_table, int i)
{
	return (env_table->func[i](env_table, env_table->cmdgroups[0].args));
}

int	run_builtins(t_env *env_table, int m)
{
	int	i;

	i = -1;
	printf("args [%s]\n", env_table->cmdgroups[m].args[0]);
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
		return (run_one_command(env_table, i));
	}
	return (i);
}

int one_child(t_env *env_table, char **envp, int *pid)
{
	int ret;
	int rdrfiles[2];
	ret = 0;
	if (env_table->cmdgroups[0].args != NULL)
		ret = run_builtins(env_table, 0);
	if (ret != -1)
		return (ret);


	pid[0] = fork();
	if (pid[0] == 0)
	{
		check_rdr(0, env_table->hdoc, env_table->cmdgroups[0], rdrfiles);
		if (check_command(env_table, 0) == 0)
			call_cmd(env_table, env_table->cmdgroups[0], envp);
	}
	return (ret);
}

int	ft_pipe(t_env *env_table, char **envp)
{
	pid_t	*pid;
	int		ret;

	ret = -1;
	signal(SIGINT, sig_handler_nl);
	env_table->path = extract_path(env_table, env_table->env);
	pid = ft_calloc(env_table->nos_pipe, sizeof(int));
	if (env_table->nos_pipe > 1)
		multi_pipe(env_table, envp, pid);
	else
		ret = one_child(env_table, env_table->env, pid);
	if (ret == -1)
		wait_pid(env_table, pid);
	free(pid);
	return (ret);
}
