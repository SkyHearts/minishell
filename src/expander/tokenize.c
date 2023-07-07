/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:01:37 by jyim              #+#    #+#             */
/*   Updated: 2023/07/06 11:32:40 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*ft_strpbrk(const char *s1, const char *s2)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (s1[i])
// 	{
// 		j = 0;
// 		while (s2[j])
// 		{
// 			if (s1[i] == s2[j])
// 				return ((char *)s1 + i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// size_t	ft_strspn(const char *s, const char *accept)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (s[i])
// 	{
// 		j = 0;
// 		while (accept[j] != s[i])
// 		{
// 			if (accept[j] == '\0')
// 				return (i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_strtok(char *str, const char *delim)
// {
// 	static char	*last_token = NULL;
// 	char		*token;

// 	token = NULL;
// 	if (str == NULL)
// 		str = last_token;
// 	str += ft_strspn(str, delim);
// 	if (*str == '\0')
// 		return (NULL);
// 	token = str;
// 	str = ft_strpbrk(token, delim);
// 	if (str == NULL)
// 		last_token = token + ft_strlen(token);
// 	else
// 	{
// 		*str = '\0';
// 		last_token = str + 1;
// 	}
// 	return (token);
// }

// //char	*argv_to_str(char **argv)
// //{
// //	int		i;
// //	char	*str_pile;
// //	char	*token_buff;

// //	i = 1;
// //	str_pile = ft_strdup("");
// //	while (argv[i])
// //	{
// //		token_buff = ft_strtok(argv[i], " ");
// //		if (ft_strcmp(str_pile, ""))
// //			str_pile = ft_strjoin(str_pile, " ");
// //		while (token_buff != NULL)
// //		{
// //			str_pile = ft_strjoin(str_pile, token_buff);
// //			token_buff = ft_strtok(NULL, " ");
// //			if (token_buff != NULL)
// //				str_pile = ft_strjoin(str_pile, " ");
// //		}
// //		i++;
// //	}
// //	return (str_pile);
// //}

// // word1 word2
// char	*reduce_white_spaces(char *s, int need_free)
// {
// 	int		i;
// 	char	*str_pile;
// 	char	*token_buff;

// 	i = 0;
// 	str_pile = ft_strdup("");
// 	if (s != NULL)
// 	{
// 		token_buff = ft_strtok(s, " ");
// 		//if (ft_strcmp(str_pile, ""))
// 		//{
// 		//	str_pile = ft_strjoin_f(str_pile, " ");
// 		//}
// 		while (token_buff != NULL)
// 		{
// 			//printf("Here[%d]\n", i++);
// 			//printf("token[%s]\n", token_buff);
// 			str_pile = ft_strjoin_f(str_pile, token_buff);
// 			//printf("str_pile[%s]\n", str_pile);
// 			token_buff = ft_strtok(NULL, " ");
// 			if (token_buff != NULL)
// 				str_pile = ft_strjoin_f(str_pile, " ");
// 		}
// 	}
// 	if (need_free)
// 		free(s);
// 	return (str_pile);
// }

/* Reduces white space by moving characther to the front */
//char	*reduce_white_spaces_2(char *s)
//{
//	int		i;
//	int		j;
//	int		size;
//	char	quote_type;
//	char	*str;

//	i = 0;
//	j = 0;
//	size = strlen(s);
//	str = malloc (sizeof(char) * (size + 1));
//	while (s[i])
//	{
//		if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
//		{
//			quote_type = s[i];
//			str[j++] = s[i++];
//			// printf("quote:%c\n",s[i]);
//			while (s[i] && s[i] != quote_type)
//			{
//				// printf("quote:%c\n",s[i]);
//				str[j++] = s[i++];
//			}
//		}
//		if(s[i] == ' ')
//		{
//			while (s[i] && s[i] == ' ' && s[i + 1] != ' ')
//				i++;
//		}
//		// printf("out:%c\n",s[i]);
//		str[j++] = s[i++];
//	}
//	str[j] == '\0';
//	return (str);
//}


void 	reduce_white_spaces_3(char *s)
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE || s[i] == DOUBLE_QUOTE)
		{
			quote_type = s[i];
			s[j++] = s[i++];
			//printf("quote:%c\n",s[i]);
			while (s[i] && s[i] != quote_type)
			{
				//printf("quote:%c\n",s[i]);
				s[j++] = s[i++];
			}
		}
		if (!isspace(s[i]) || (i > 0 && !isspace(s[i - 1])))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

//#include <ctype.h>
//#include <stdio.h>
//// "echo world"
//int main(void)
//{
//	char str[] = "  \"hello   \'     world\"    my name 'is  \"    jj'                 \0";
	
//	// reduce_white_spaces_2(str);
//	printf("%s\n", reduce_white_spaces_2(str));
//	reduce_white_spaces_3(str);
//	printf("%s\n", str);
//}

// #include <ctype.h>
// #include <stdio.h>

// void strip_extra_spaces(char* str) {
//   int i, x;
//   for(i=x=0; str[i]; ++i)
//     if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1])))
//       str[x++] = str[i];
//   str[x] = '\0';
// }

// int main(int argc, char* argv[]) {
//   char str[] = "  If  you  gaze   into  the abyss,    the   abyss gazes also   into you.    ";
//   strip_extra_spaces(str);
//   printf("%s\n",str);
//   return 0;
// }