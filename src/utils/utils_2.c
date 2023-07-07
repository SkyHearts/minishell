/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:31:30 by jyim              #+#    #+#             */
/*   Updated: 2023/07/07 15:55:30 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	return (0);
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

char	*ft_strcat(char *s1, const char *s2)
{
	char	*dest;

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
	//printf("joined length [%zu]\n", join_len);
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
