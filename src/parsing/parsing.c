/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:48 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 14:50:20 by sulim            ###   ########.fr       */
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
void	rdr_to_cmdgroups(t_rdrinfo *rdr_info, char **s, int *start, int end)
{
	int	i;

	i = 0;
	while (s[(*start)] && (*start) < end)
	{
		//printf("s[%d]: [%s]\n", *start, s[*start]);
		if (is_rdr(s[(*start)]))
		{
			//printf("Copy rdr_type s[%d]: [%s]\n", *start, s[*start]);
			(rdr_info)[i].rdr_type = is_rdr(s[(*start)++]);
			if (!is_operator(s[(*start)]))
			{
				(rdr_info)[i].rdr_str = ft_strdup(s[(*start)]);
				//printf("Copy rdr_str s[%d]: [%s]\n", *start, (rdr_info)[i].rdr_str);
			}
			else
				rdr_info[i].rdr_str = NULL;
			i++;
		}
		(*start)++;
	}
	//rdr_info[i].rdr_str = NULL;
	//rdr_info[i].rdr_type = EMPTY;
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

	i = -1;
	j = 0;
	start = 0;
	while (splitted[++i])
	{
		if (is_pipes(splitted[i]) || splitted[i + 1] == NULL)
		{
			// printf("Insert cmdgroups[%d].rdr\n", j);
			// printf("Start :[%d]  End :[%d]\n", start, i);
			info = (t_rdrinfo *)malloc (sizeof(t_rdrinfo)
					* (cmdgroups[j].rdr_count + 1));
			rdr_to_cmdgroups(info, splitted, &start, i);
			cmdgroups[j].rdr_info = info;
			j++;
		}
		else if (is_rdr(splitted[i]))
			cmdgroups[j].rdr_count++;
		// printf("cmdgroups[%d].rdr_count : [%d]\n", j, cmdgroups[j].rdr_count);
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
	// if (!(cmdgroups)[j].args)
	// {
	// 	(cmdgroups)[j].args = NULL;
	// }
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
	// printf("number of pipes : [%d]\n", env_table->nos_pipe + 1);
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

	splitted = ft_split_quoted(input, ' ');
	handle_dollarsign(splitted, env_table, 0);
	init_pipegroupsv2(splitted, env_table);
	env_table->hdoc = handle_heredoc(env_table);
	ret = syntax_checking(splitted);
	// printf("ret: [%d]\n", ret);
	if (ret > 0)
	{
		free_doublearray(splitted);
		free_var(env_table);
		return (env_table->errnumber = ret, ret);
	}
	free_doublearray(splitted);
	return (0);
}
