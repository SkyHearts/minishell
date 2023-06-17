/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:09:36 by jyim              #+#    #+#             */
/*   Updated: 2023/06/16 16:52:41 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void			exec_others(t_pipe **cmdgroups, t_env env_table)
{
	int		status;
	char	*path;
	char	**argv;
	pid_t	child;

	argv = (*cmdgroups[0]).args;
	path = find_path(argv[0], envs);
	if (!path)
	{
		ft_puterror_fd(argv[0], ": command not found", 2);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(path, argv, g_envp) == -1)
			exit(ft_puterror_fd(argv[0], ": command not found", 2));
		exit(EXIT_SUCCESS);
	}
	wait(&status);
}

void	exec_cmds()
{
	// if (has_pipe())
	// 	exec_pipe();
	// else if (has_redir())
	// 	exec_redir();
	// else if (!exec_dollar() && !exec_builtin())
		exec_others();
}