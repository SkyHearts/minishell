/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:45:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/13 19:38:41 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error(char *err)
{
	perror(err);
	exit(1);
}

int	has_pipes(char **splitted)
{
	int	i;
	int pipes;

	i = -1;
	pipes = 1;
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

void free_doublearray(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

char	**copy_and_free_doublearray(char **src, char *s, int size)
{
	int		i;
	char	**tmp_table;

	i = 0;
	tmp_table = (char **)malloc (sizeof(char *) * (size + 2));
	while (src[i] != NULL)
	{
		tmp_table[i] = ft_strdup(src[i]);
		// printf("copying %s, i: %d\n", tmp_table[i], i);
		i++;
	}
	free_doublearray(src);
	// printf("Append string : %s$, i: %d\n", s, i);
	tmp_table[i] = ft_strdup(s);
	tmp_table[++i] = NULL;
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
		temp_args[0] = ft_strdup(str);
		temp_args[1] = NULL;
		// printf("temp_args[0]: %s\n", temp_args[0]);
		return (temp_args);
	}
	while (args[i])
		i++;
	// printf("Current size: %d\n", i);
	temp_args = copy_and_free_doublearray(args, str, i);
	// print_darray(temp_args);
	return (temp_args);
}