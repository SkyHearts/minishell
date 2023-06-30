/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:01:37 by jyim              #+#    #+#             */
/*   Updated: 2023/06/29 13:13:05 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j] != s[i])
		{
			if (accept[j] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token;

	token = NULL;
	if (str == NULL)
		str = last_token;
	str += ft_strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	token = str;
	str = ft_strpbrk(token, delim);
	if (str == NULL)
		last_token = token + ft_strlen(token);
	else
	{
		*str = '\0';
		last_token = str + 1;
	}
	return (token);
}

char	*argv_to_str(char **argv)
{
	int		i;
	char	*str_pile;
	char	*token_buff;

	i = 1;
	str_pile = ft_strdup("");
	while (argv[i])
	{
		token_buff = ft_strtok(argv[i], " ");
		if (ft_strcmp(str_pile, ""))
			str_pile = ft_strjoin(str_pile, " ");
		while (token_buff != NULL)
		{
			str_pile = ft_strjoin(str_pile, token_buff);
			token_buff = ft_strtok(NULL, " ");
			if (token_buff != NULL)
				str_pile = ft_strjoin(str_pile, " ");
		}
		i++;
	}
	return (str_pile);
}

char	*reduce_white_spaces(char *s, int need_free)
{
	int		i;
	char	*str_pile;
	char	*token_buff;

	i = 1;
	str_pile = ft_strdup("");
	if (s != NULL)
	{
		token_buff = ft_strtok(s, " ");
		if (ft_strcmp(str_pile, ""))
			str_pile = ft_strjoin_f(str_pile, " ");
		while (token_buff != NULL)
		{
			str_pile = ft_strjoin_f(str_pile, token_buff);
			token_buff = ft_strtok(NULL, " ");
			if (token_buff != NULL)
				str_pile = ft_strjoin_f(str_pile, " ");
		}
		i++;
	}
	if (need_free)
		free(s);
	return (str_pile);
}
