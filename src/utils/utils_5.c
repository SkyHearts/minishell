/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:57:50 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 20:03:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_f(char *s1, char *s2)
{
	size_t	join_len;
	size_t	i;
	size_t	j;
	char	*strjoin;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	join_len = ft_strlen_n(s1) + ft_strlen_n(s2);
	strjoin = malloc(sizeof(char) * (join_len) + 1);
	if (!strjoin)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (strjoin);
}

int	is_operator_char(char c)
{
	if (c == PIPE || c == REDIRECT_LEFT || c == REDIRECT_RIGHT)
		return (1);
	return (0);
}

char	is_onlypipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]) && !is_operator_char(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	split_len(char **split)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (split[++i])
	{
		if (!isempty(split[i]))
			size++;
	}
	return (size);
}

char	**clear_empty(char **split)
{
	int		size;
	char	**rsplit;
	int		i;
	int		j;

	i = -1;
	size = split_len(split);
	rsplit = malloc(sizeof(char *) * (size + 1));
	if (!rsplit)
		return (NULL);
	i = -1;
	j = 0;
	while (split[++i])
	{
		if (!isempty(split[i]))
			rsplit[j++] = split[i];
	}
	rsplit[j] = NULL;
	return (free(split), rsplit);
}
