/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:46:50 by sulim             #+#    #+#             */
/*   Updated: 2023/07/07 15:42:22 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	last_child(t_env *env_table, t_pipe pipe, int m, char **envp, int pipe_fd[2][2])
{
	int rdrfiles[2];
	
	ft_dup(m, pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, m);
}

void	middle_child(t_env *env_table, t_pipe pipe, int m, char **envp, int pipe_fd[2][2])
{
	int rdrfiles[2];
	
	ft_dup(m, pipe_fd[0][1], STDOUT_FILENO);
	ft_dup(m ,pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, m);
}

void	first_child(t_env *env_table, t_pipe pipe, int m, char **envp, int pipe_fd[2][2])
{
	int rdrfiles[2];
	
	ft_dup(m, pipe_fd[0][1], STDOUT_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, pipe, envp, m);
}

void	parent(int num_pipe, int m, int pipe_fd[2][2])
{
	if (m != 0)
	{
		// middle, last
		close(pipe_fd[1][0]);
	}
	if (m != num_pipe - 1)
	{
		// first cmd, middle cmd
		pipe_fd[1][0] = pipe_fd[0][0];
	}
	// all
	close(pipe_fd[0][1]);
	if (m == num_pipe - 1)
	{
		// last
		close(pipe_fd[0][0]);
	}
}

void	multi_pipe(t_env *env_table, char **envp, int *pid)
{
	int		pipe_fd[2][2];
	int		m;
 
	m = -1;
	while (++m < env_table->nos_pipe)
	{
		// pipe(pipe_fd[0]);
		if (m < env_table->nos_pipe && pipe(pipe_fd[0]) == -1)
		{
			printf("Bad pipe [%d]", m);
			exit(1);
		}
		pid[m] = fork();
		if (pid[m] == 0)
		{
			if (m == 0)
				first_child(env_table, env_table->cmdgroups[m], m, envp, pipe_fd);
			else if (m == env_table->nos_pipe - 1)
				last_child(env_table, env_table->cmdgroups[m], m, envp, pipe_fd);
			else
				middle_child(env_table, env_table->cmdgroups[m], m, envp, pipe_fd);
		}
		else
			parent(env_table->nos_pipe, m, pipe_fd);
	}
}