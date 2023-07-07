/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:33:32 by jyim              #+#    #+#             */
/*   Updated: 2023/06/30 15:21:25 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_doublearray(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

void	exit_error(void)
{
	printf("ERROR!!!");
	exit(1);
}

size_t	ft_strlen_n(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c] != '\0')
		c++;
	return (c);
}
