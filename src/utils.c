/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:45:48 by jyim              #+#    #+#             */
/*   Updated: 2023/06/24 15:20:32 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error(char *err)
{
	perror(err);
	exit(1);
}

int	ft_isalpha_equal(int c)
{
	if ((c >= 65 && c <= 90) || c == '=')
		return (c);
	else if ((c >= 97 && c <= 122) || c == '=')
		return (c);
	else
		return (0);
}

int	ft_isalnum_q(int c)
{
	if ((c >= 65 && c <= 90) || c == '?')
		return (c);
	else if (c >= 97 && c <= 122)
		return (c);
	else if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}

int	has_pipes(char **splitted)
{
	int	i;
	int	pipes;

	i = -1;
	pipes = 1;
	while (splitted[++i])
	{
		if (!ft_strcmp(splitted[i], "|"))
			pipes++;
	}
	return (pipes);
}

int	is_pipes(char *splitted)
{
	if (!ft_strcmp(splitted, "|"))
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "|"))
		return (3);
	return(0);
}

int	is_rdr(char *splitted)
{
	if (!ft_strcmp(splitted, "<"))
		return (1);
	if (!ft_strcmp(splitted, ">"))
		return (2);
	if (!ft_strcmp(splitted, "<<"))
		return (3);
	if (!ft_strcmp(splitted, ">>"))
		return (4);
	return (0);
}

void	free_doublearray(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

int	str_size_quote(const char *input)
{
	char	quote_type;
	int		i;
	int		size;

	i = -1;
	quote_type = -1;
	size = 0;
	while (input[++i])
	{
		if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			quote_type = input[i];
			while (input[++i] && input[i] != quote_type)
				size++;
		}
		if (input[i] != SINGLE_QUOTE && input[i] != DOUBLE_QUOTE)
			size++;
		if (!input[i])
			return (size);
	}
	return (size);
}

char	*ft_strdup_quote(const char *src)
{
	int		j;
	int		i;
	char	quote;
	char	*srccpy;

	j = 0;
	i = -1;
	srccpy = (char *) malloc(sizeof(char) * (str_size_quote(src) + 1));
	if (!srccpy)
		return (NULL);
	while (src[++i])
	{
		if (src[i] == SINGLE_QUOTE || src[i] == DOUBLE_QUOTE)
		{
			quote = src[i];
			while (src[++i] && src[i] != quote)
				srccpy[j++] = src[i];
		}
		if (src[i] != SINGLE_QUOTE && src[i] != DOUBLE_QUOTE)
			srccpy[j++] = src[i];
		if (!src[i])
			return (srccpy[j] = '\0', srccpy);
	}
	return (srccpy[j] = '\0', srccpy);
}

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

char	**ft_append_2d(char **args, char *str)
{
	int		i;
	char	**temp_args;

	i = 0;
	// printf("Appending spllited: %s$\n", str);
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

char	*ft_strcat(char *s1, const char *s2)
{
	char *dest;
	
	dest = s1;
	while (*s1)
		s1++;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (dest);
}