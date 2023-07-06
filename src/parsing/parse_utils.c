/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:41 by jyim              #+#    #+#             */
/*   Updated: 2023/07/05 19:00:57 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(char *input)
{
	char	quote_type;
	int		boolean;
	int		i;

	i = -1;
	quote_type = -1;
	boolean = 0;
	while (input[++i])
	{
		if (if_quotes(input[i]))
		{
			boolean = 1;
			quote_type = input[i];
			while (input[++i] && input[i] != quote_type)
				continue ;
			if (!input[i])
				return (boolean);
			boolean = 0;
		}
	}
	return (boolean);
}

int	unsigned_operators(char *split)
{
	if (!ft_strncmp(split, ">>>", 3))
		printf("syntax error near unexpected token >>>\n");
	else if (!ft_strncmp(split, "<<<", 3))
		printf("syntax error near unexpected token <<<\n");
	return (258);
}

// 0   1  2 3   4
// < text | > text
int	pipe_operators(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{	
		if ((is_operator(split[i]) && split[i + 1]))
		{
			printf("Here1\n");
			if (split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_pipes(split[i]) && split[i + 1] == NULL)
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			else if (is_rdr(split[i]) && is_operator(split[i + 1]))
				return (printf("syntax error near unexpected token '%s'\n", split[i + 1]), 258);
			else if (is_pipes(split[i]) && is_operator(split[i + 1]))
			{
				if (split[i + 2] == NULL || is_operator(split[i + 2]))
					printf("syntax error near unexpected token '%s'\n", split[i]);
				return (printf("syntax error near unexpected token '%s'\n", split[i]), 258);
			}
		}
		i++;
	}
	return (0);
}

//int	rdr_operators(char *s, char *s_plus_1, char *s_plus_2)
//{
//	if (is_operator(s_plus_1) == 3)
//		printf("syntax error near unexpected token 'newline'\n");
//	else if (is_pipes(s) && is_operator(s_plus_1))
//	{
//		if (!is_operator(s_plus_2))
//			return (0);
//		printf("syntax error near unexpected token here2'%s'\n",
//			s);
//	}
//	return (258);
//}

int	syntax_checking(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (is_operator(split[i]) == 4)
			return (unsigned_operators(split[i]));
		if ((pipe_operators(split)) == 258)
			return (258);
	}
	return (0);
}

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	c;

// 	c = 0;
// 	while (s1[c] != '\0' || s2[c] != '\0')
// 	{	
// 		if (s1[c] != s2[c])
// 			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
// 		c++;
// 	}
// 	return (0);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	c;

// 	c = 0;
// 	while (c < n && (s1[c] != '\0' || s2[c] != '\0'))
// 	{	
// 		if (s1[c] != s2[c])
// 			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
// 		c++;
// 	}
// 	return (0);
// }


// int	is_pipes(char *splitted)
// {
// 	if (!ft_strcmp(splitted, "|"))
// 		return (1);
// 	return (0);
// }

// int	is_operator(char *str)
// {
// 	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
// 		return (1);
// 	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
// 		return (2);
// 	if (!ft_strcmp(str, "|"))
// 		return (3);
// 	if (!ft_strncmp(str, ">>>", 3) || !ft_strncmp(str, "<<<", 3))
// 		return (4);
// 	return (0);
// }

// int	is_rdr(char *splitted)
// {
// 	if (!ft_strcmp(splitted, "<"))
// 		return (1);
// 	if (!ft_strcmp(splitted, ">"))
// 		return (2);
// 	if (!ft_strcmp(splitted, "<<"))
// 		return (3);
// 	if (!ft_strcmp(splitted, ">>"))
// 		return (4);
// 	return (0);
// }

// void	*ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*temp;

// 	temp = s;
// 	while (n > 0)
// 	{
// 	*temp++ = 0;
// 	n--;
// 	}
// 	return (temp);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (0);
// 	ft_bzero (ptr, size * count);
// 	return (ptr);
// }

// int	syntax_size(char **split)
// {
// 	int	size;
// 	int	i;

// 	size = 0;
// 	i = 0;
// 	while (split[i])
// 	{
// 		if (is_operator(split[i]))
// 		{
// 			if (is_operator(split[i]) == 3)
// 				size++;
// 			else if (is_rdr(split[i]) && split[i + 1]
// 				&& !is_operator(split[i + 1]))
// 				size += 2;
// 			else if (is_rdr(split[i]))
// 				size += 1;
// 		}
// 		i++;
// 	}
// 	return (size);
// }
// //    0     1       2        3     4      5       6      7      8      9   
// // {"<<", "eof", "echo", "hello", "|", "echo", "world", "<", "test2", NULL}
// char	**syntax_split(char **split)
// {
// 	int		size;
// 	int		i;
// 	int		j;
// 	char	**s_split;

// 	size = syntax_size(split);
// 	s_split = ft_calloc(sizeof(char *), size + 1);
// 	j = -1;
// 	i = 0;
// 	while (split[i])
// 	{
// 		if (is_operator(split[i]) == 3)
// 			s_split[++j] = strdup(split[i]);
// 		else if (is_rdr(split[i]) && split[i + 1]
// 			&& !is_operator(split[i + 1]))
// 		{
// 			s_split[++j] = strdup(split[i]);
// 			s_split[++j] = strdup(split[i + 1]);
// 		}
// 		else if (is_rdr(split[i]))
// 			s_split[++j] = strdup(split[i]);
// 		i++;
// 	}
// 	s_split[++j] = NULL;
// 	return (s_split);
// }

// int	pipe_operators(char **s_split)
// {
// 	int	i;

// 	i = 0;
// 	if (is_pipes(s_split[0]))
// 	{
// 		printf("syntax error near unexpected token '%s'\n", s_split[0]);
// 		return (258);
// 	}
// 	while (s_split[i])
// 	{
// 		if (is_operator(s_split[i]) && !s_split[i + 1])
// 		{
// 			if (is_pipes(s_split[i]))
// 				printf("syntax error near unexpected token '%s'\n", s_split);
// 			else
// 				printf("syntax error near unexpected token 'newline'\n");
// 		}
// 	}
// 	return (258);
// }

// int	syntax_checking(char **splitted)
// {
// 	char	**s_split;
// 	int		i;

// 	s_split = syntax_split(splitted);
// 	if (pipe_operators(s_split));
// 		return (258);
// 	return (free(s_split), 0);
// }

// int	main(void)
// {
// 	char *str[] = {"<<", "eof", "echo", "hello", "|", "echo", "world", "<", "test2", ">", "text", NULL};

// 	// printf("str size = [%d]\n", syntax_size(str));
// 	char **split = syntax_split(str);
// 	int k = -1;
// 	while (++k < syntax_size(str))
// 		printf("spit[%d]: [%s]\n", k, split[k]);
// }
