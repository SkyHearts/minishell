/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:46:50 by sulim             #+#    #+#             */
/*   Updated: 2023/07/08 12:27:57 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	last_child(t_env *env_table, int m, char **envp, int pipe_fd[2][2])
{
	int	rdrfiles[2];

	ft_dup(pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, env_table->cmdgroups[m], envp, m);
}

void	middle_child(t_env *env_table, int m, char **envp, int pipe_fd[2][2])
{
	int	rdrfiles[2];

	ft_dup(pipe_fd[0][1], STDOUT_FILENO);
	ft_dup(pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, env_table->cmdgroups[m], envp, m);
}

void	first_child(t_env *env_table, int m, char **envp, int pipe_fd[2][2])
{
	int	rdrfiles[2];

	ft_dup(pipe_fd[0][1], STDOUT_FILENO);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	check_rdr(m, env_table->hdoc, env_table->cmdgroups[m], rdrfiles);
	if (check_command(env_table, m) == 0)
		call_cmd(env_table, env_table->cmdgroups[m], envp, m);
}

// middle, last
// first cmd, middle cmd
// last
void	parent(int num_pipe, int m, int pipe_fd[2][2])
{
	if (m != 0)
		close(pipe_fd[1][0]);
	if (m != num_pipe - 1)
		pipe_fd[1][0] = pipe_fd[0][0];
	close(pipe_fd[0][1]);
	if (m == num_pipe - 1)
		close(pipe_fd[0][0]);
}

void	multi_pipe(t_env *env_table, char **envp, int *pid)
{
	int		pipe_fd[2][2];
	int		m;

	m = -1;
	while (++m < env_table->nos_pipe)
	{
		if (m < env_table->nos_pipe && pipe(pipe_fd[0]) == -1)
		{
			ft_printf("Bad pipe [%d]", m);
			exit(1);
		}
		pid[m] = fork();
		if (pid[m] == 0)
		{
			if (m == 0)
				first_child(env_table, m, envp, pipe_fd);
			else if (m == env_table->nos_pipe - 1)
				last_child(env_table, m, envp, pipe_fd);
			else
				middle_child(env_table, m, envp, pipe_fd);
		}
		else
			parent(env_table->nos_pipe, m, pipe_fd);
	}
}
