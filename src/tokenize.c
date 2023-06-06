/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:01:37 by jyim              #+#    #+#             */
/*   Updated: 2023/06/06 10:41:28 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	static char *last_token = NULL;  // keep track of last token
	char *token = NULL;  // current token
	
	// last_token = NULL;
	// token = NULL;
	// if str is NULL, continue from the last token
	if (str == NULL)
		str = last_token;
	// find the start of the next token
	str += ft_strspn(str, delim);
	// if token is already null at the start, return null
	if (*str == '\0')
		//last_token = NULL;
		return (NULL);
	// find the end of the token
	token = str;
	str = ft_strpbrk(token, delim);
	if (str == NULL)
		last_token = token + ft_strlen(token);
	else
	{
		*str = '\0';  // terminate the token
		last_token = str + 1;  // save the rest for next time
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
		if (strcmp(str_pile, ""))
			str_pile = ft_strjoin(str_pile, " ");
		// printf("%s\n", token_buff);
		while (token_buff != NULL)
		{
			str_pile = ft_strjoin(str_pile, token_buff);
			token_buff = ft_strtok(NULL, " ");
			if (token_buff != NULL)
				str_pile = ft_strjoin(str_pile, " ");
			// printf("%s\n", token_buff);
		}
		i++;
	}
	// printf("%s\n", str_pile);
	return (str_pile);
}

char	*reduce_white_spaces(char *s)
{
	int		i;
	char	*str_pile;
	char	*token_buff;

	i = 1;
	str_pile = ft_strdup("");
	if (s != NULL)
	{
		token_buff = ft_strtok(s, " ");
		if (strcmp(str_pile, ""))
			str_pile = ft_strjoin(str_pile, " ");
		// printf("%s\n", token_buff);
		while (token_buff != NULL)
		{
			str_pile = ft_strjoin(str_pile, token_buff);
			token_buff = ft_strtok(NULL, " ");
			if (token_buff != NULL)
				str_pile = ft_strjoin(str_pile, " ");
			// printf("%s\n", token_buff);
		}
		i++;
	}
	// printf("%s\n", str_pile);
	return (str_pile);
}

void	exit_error(void)
{
	printf("ERROR!");
	exit(1);
}
