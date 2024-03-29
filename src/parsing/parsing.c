/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 19:18:44 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// 1  2  3 4  5
// 0  1  2 3  4
// < ASD | > ZXC
// First cmd[0].info[2]
// 1st iter : start = 0, end = 2
// info[0].rdr_type = IN
// info[0].rdr_str = ASD
// 2nd iter : start = 2, end = 4
// info[1].rdr_type = OUT
// info[1].rdr_str = ZXC
int	rdr_to_cmdgroups(t_rdrinfo *rdr_info, char **s, int *start, int end)
{
	int	i;

	i = 0;
	while (s[(*start)] && (*start) < end)
	{
		if (is_rdr(s[(*start)]))
		{
			(rdr_info)[i].rdr_type = is_rdr(s[(*start)++]);
			if (!is_operator(s[(*start)]))
			{
				(rdr_info)[i].rdr_str = ft_strdup(s[(*start)]);
			}
			else
				rdr_info[i].rdr_str = ft_strdup("");
			i++;
		}
		else
			(*start)++;
	}
	return (0);
}

// 1  2  3 4  5
// < ASD | > ZXC
// First cmd[0].info[2]
void	input_rdr(char **splitted, t_pipe *cmdgroups)
{
	int			i;
	int			j;
	int			start;
	t_rdrinfo	*info;

	i = 0;
	j = 0;
	start = 0;
	while (i <= split_len(splitted))
	{
		if (is_pipes(splitted[i]) || splitted[i] == NULL)
		{
			info = (t_rdrinfo *)malloc (sizeof(t_rdrinfo)
					* (cmdgroups[j].rdr_count + 1));
			rdr_to_cmdgroups(info, splitted, &start, i);
			cmdgroups[j].rdr_info = info;
			j++;
		}
		else if (is_rdr(splitted[i]))
			cmdgroups[j].rdr_count++;
		i++;
	}
}

/* Parse all input into cmdgroups */
void	input_commands(char **splitted, t_pipe *cmdgroups)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (splitted[++i])
	{	
		if (is_rdr(splitted[i]) && splitted[i + 1])
			i++;
		else if (!is_rdr(splitted[i]) && !is_pipes(splitted[i]))
		{
			(cmdgroups)[j].args = ft_append_2d
				((cmdgroups)[j].args, splitted[i]);
		}
		else if (is_pipes(splitted[i]) && splitted[i])
			j++;
	}
}

// 1  2  3 4  5
// < ASD | > ZXC
// cmdgroups[3]
void	init_pipegroupsv2(char **splitted, t_env *env_table)
{
	int		i;
	t_pipe	*cmdgroups;

	i = -1;
	env_table->nos_pipe = has_pipes(splitted);
	env_table->cmdgroups = (t_pipe *)malloc (sizeof(t_pipe)
			* (env_table->nos_pipe + 1));
	cmdgroups = env_table->cmdgroups;
	while (++i < (env_table->nos_pipe + 1))
	{
		(cmdgroups)[i].args = NULL;
		(cmdgroups)[i].rdr_info = NULL;
		(cmdgroups)[i].rdr_count = 0;
	}
	input_commands(splitted, cmdgroups);
	input_rdr(splitted, cmdgroups);
}

int	parse_cmds(char *input, t_env *env_table)
{
	char	**splitted;
	int		ret;

	ret = 0;
	splitted = ft_split_quoted(input, ' ');
	handle_dollarsign(splitted, env_table, 0);
	splitted = clear_empty(splitted);
	init_pipegroupsv2(splitted, env_table);
	ret = syntax_checking(splitted);
	if (ret > 0)
	{
		free_doublearray(splitted);
		free_var(env_table);
		return (env_table->errnumber = ret, ret);
	}
	env_table->hdoc = handle_heredoc(env_table);
	free_doublearray(splitted);
	return (0);
}
