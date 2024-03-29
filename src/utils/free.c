/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:37:41 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 20:11:34 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmdgroups(t_env *env_table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < env_table->nos_pipe)
	{
		if (env_table->cmdgroups[i].args != NULL)
			free_doublearray(env_table->cmdgroups[i].args);
		j = 0;
		while (j < env_table->cmdgroups[i].rdr_count)
		{
			free(env_table->cmdgroups[i].rdr_info[j].rdr_str);
			j++;
		}
		if (env_table->cmdgroups[i].rdr_info != NULL)
			free(env_table->cmdgroups[i].rdr_info);
		i++;
	}
	free(env_table->cmdgroups);
}

//free_doublearray(env_table->heredoc_cmd);
void	free_var(t_env *env_table)
{
	free_cmdgroups(env_table);
	if (env_table->hdoc != NULL)
	{
		free_doublearray(env_table->hdoc);
		env_table->hdoc = NULL;
	}
}

void	free_all(t_env *env_table)
{
	free_doublearray(env_table->env);
	if (env_table->path)
		free_doublearray(env_table->path);
	free_doublearray(env_table->functions);
	free_cmdgroups(env_table);
	if (env_table->hdoc != NULL)
		free_doublearray(env_table->hdoc);
	rl_clear_history();
}

// void	free_hdoc(t_env *env_table)
// {
// 	int	i;

// 	i = -1;
// 	while (i < env_table->nos_pipe)
// 	{
// 		if (env_table->heredoc_cmd[i] == NULL)
// 			continue ;
// 		else
// 			free (env_table->heredoc_cmd[i]);
// 	}
// 	free (env_table->heredoc_cmd);
// }

	//free_hdoc(env_table);
		//free_doublearray(env_table->rl_buffer);
	//free_doublearray(env_table->heredoc_cmd);