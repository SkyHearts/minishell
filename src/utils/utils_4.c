/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:35:59 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 10:35:02 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**copy_and_free_doublearray(char **src, char *s, int size)
{
	int		i;
	char	**tmp_table;

	i = 0;
	tmp_table = (char **)malloc (sizeof(char *) * (size + 2));
	while (src[i] != NULL)
	{
		tmp_table[i] = ft_strdup_quote(src[i]);
		i++;
	}
	free_doublearray(src);
	tmp_table[i] = ft_strdup_quote(s);
	tmp_table[++i] = NULL;
	return (tmp_table);
}

/*
 Duplicates a 2d array and append an array to the end of the 2d array.
 Free the previous 2d array at the end.
*/
char	**ft_append_2d(char **args, char *str)
{
	int		i;
	char	**temp_args;

	i = 0;
	if (args == NULL)
	{
		temp_args = (char **)malloc (sizeof(char *) * 2);
		temp_args[0] = ft_strdup_quote(str);
		temp_args[1] = NULL;
		return (temp_args);
	}
	while (args[i])
		i++;
	temp_args = copy_and_free_doublearray(args, str, i);
	return (temp_args);
}

char	**copy_doublearray(char **src, char *s, int size)
{
	int		i;
	char	**tmp_table;

	i = 0;
	tmp_table = (char **)malloc (sizeof(char *) * (size + 2));
	while (src[i] != NULL)
	{
		tmp_table[i] = src[i];
		i++;
	}
	//free(src);
	tmp_table[i] = s;
	tmp_table[++i] = NULL;
	return (tmp_table);
}

/*
 Copy a 2d array and append an array to the end of the 2d array.
 Free the previous pointer at the end.
*/
char	**ft_append_2d_nf(char **args, char *str)
{
	int		i;
	char	**temp_args;

	i = 0;
	if (args == NULL)
	{
		temp_args = (char **)malloc (sizeof(char *) * 2);
		temp_args[0] = str;
		temp_args[1] = NULL;
		return (temp_args);
	}
	while (args[i])
		i++;
	// printf("append_nf size: %d\n", i);
	temp_args = copy_doublearray(args, str, i);
	free(args);
	return (temp_args);
}
