/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:45:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/10 18:31:55 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	has_pipes(char **splitted)
{
	int	i;
	int pipes;

	i = -1;
	pipes = 0;
	while (splitted[++i])
	{
		if (!ft_strcmp(splitted[i],"|"))
			pipes++;
	}
	return (pipes);
}

int	is_pipes(char *splitted)
{
	if (!ft_strcmp(splitted,"|"))
		return (1);
	return (0);
}

int	is_rdr(char *splitted)
{
	if (!ft_strcmp(splitted,"<<"))
		return (1);
	if (!ft_strcmp(splitted,">>"))
		return (2);
	if (!ft_strcmp(splitted,"<"))
		return (3);
	if (!ft_strcmp(splitted,">"))
		return (4);
	return (0);
}

char	**copy_2d(char **src, char *s)
{
	int		i;
	char	**tmp_table;

	i = 0;
	tmp_table = NULL;
	while (src[i] != NULL)
	{
		tmp_table[i] = ft_strdup(src[i]);
		free(src[i]);
		i++;
	}
	free(src);
	tmp_table[i++] = ft_strdup(s);
	tmp_table[i] = NULL;
	return (tmp_table);
}

char **ft_append_2d(char **args, char *str)
{
	int	i;
	char **temp_args;

	i = 0;
	if (args == NULL)
	{
		temp_args = (char **)malloc (sizeof(char *) * 2);
		temp_args[0] = strdup(str);
		temp_args[1] = NULL;
		return (args);
	}
	while (args[i])
		i++;
	temp_args = (char **)malloc (sizeof(char *) * i + 2);
	temp_args = copy_2d(args, str);
	print_darray(temp_args);
	return (temp_args);
}