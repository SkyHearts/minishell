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

void	wait_pid(t_env *env_table, int *pid)
{
	int	status;
	int	i;

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
			ft_printf("waitpid error");
	}
}

int	run_one_command(t_env *env_table, int i)
{
	return (env_table->func[i](env_table, env_table->cmdgroups[0].args));
}

int	run_builtins(t_env *env_table, int m)
{
	int	i;

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
		return (run_one_command(env_table, i));
	}
	return (i);
}

int	one_child(t_env *env_table, char **envp, int *pid)
{
	int	ret;
	int	rdrfiles[2];

	ret = 0;
	if (env_table->cmdgroups[0].args != NULL)
	{
		ret = run_builtins(env_table, 0);
		if (ret != -1)
			return (ret);
	}
	pid[0] = fork();
	if (pid[0] == 0)
	{
		check_rdr(0, env_table->hdoc, env_table->cmdgroups[0], rdrfiles);
		if (check_command(env_table, 0) == 0)
			call_cmd(env_table, env_table->cmdgroups[0], envp, 0);
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
