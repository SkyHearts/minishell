/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:36:18 by jyim              #+#    #+#             */
/*   Updated: 2023/06/30 13:21:08 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_hdoc(char *eof)
{
	char	*input;
	char	*tmp1;
	char	*rstr;

	rstr = NULL;
	if (eof == NULL)
		return (NULL);
	while (1)
	{
		input = readline(">");
		if (!input)
			return (NULL);
		if (!ft_strcmp(eof, input))
			break ;
		tmp1 = ft_strjoin(input, "\n");
		rstr = ft_strjoin_f(rstr, tmp1);
	}
	return (rstr);
}

char	*input_hdoc(t_env *env_table, int i)
{
	int		j;
	char	*hdoc_str;

	hdoc_str = NULL;
	j = -1;
	while (++j < env_table->cmdgroups[i].rdr_count)
	{
		if (env_table->cmdgroups[i].rdr_info[j].rdr_type == HEREDOC)
		{
			if (hdoc_str != NULL)
				free(hdoc_str);
			hdoc_str = read_hdoc(env_table->cmdgroups[i].rdr_info[j].rdr_str);
		}
	}
	if (hdoc_str == NULL)
		return (ft_strdup(" "));
	return (hdoc_str);
}

// <<eof cmd1 | cmd 2 | <<eof cmd3  \0
//      0         1          2       3
// nos_pipe = 3  malloc = 4
char	**handle_heredoc(t_env *env_table)
{
	char	**hdoc;
	int		i;

	i = -1;
	hdoc = malloc (sizeof(char *) * (env_table->nos_pipe + 1));
	while (++i < env_table->nos_pipe)
	{
		hdoc[i] = input_hdoc(env_table, i);
	}
	hdoc[i] = NULL;
	handle_dollarsign(hdoc, env_table, 1);
	return (hdoc);
}

	// int k = -1;
	// while (hdoc[++k])
	// 	printf("hdoc[%d] [%s]\n", k, hdoc[k]);