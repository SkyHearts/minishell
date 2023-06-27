/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:26:35 by jyim              #+#    #+#             */
/*   Updated: 2023/06/27 11:08:21 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_env_cont(char *splitted, int start, t_env *env_table, char **str)
{
	int		i;
	int		end;
	char	*env_var;
	int offset;
	
	i = -1;
	end = start++;
	while (splitted[++end] && ft_isalnum(splitted[end]) && !if_quotes(splitted[end]))
		continue ;
	env_var = ft_substr(splitted, start, end - start);
	if (!(*str))
		printf("Malloc failed");
	offset = ft_strlen(env_var);
	while (env_table->env[++i])
	{	
		if (!ft_strncmp((env_table->env[i]), env_var, offset))
		{
			(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
					+ ft_strlen(env_table->env[i] + offset) + 1));
			return (free(env_var), ft_strdup(env_table->env[i] + offset + 1));
		}
	}
	if (!ft_strcmp(env_var, "$?"))
		return (free(env_var), ft_itoa(env_table->errnumber));
	// printf("strlen spliited : [%lu]\n", ft_strlen(splitted));
	// printf("end : [%d]\n", end);
	// printf("start : [%d]\n", start);
	// printf("MALLOC: [%lu]\n", (ft_strlen(splitted) - (end - start + 1) + 1));
	(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
					 + 1));
	return (free(env_var), ft_strdup(""));
}

char	*find_env_var(char *s, int start)
{
	int		i;
	int		end;
	char	*env_var;
	
	i = -1;
	end = start;
	while (s[++end] && !if_quotes(s[end]) && ft_isalnum(s[end]))
		continue ;
	env_var = ft_substr(s, start, end - start);
	return (env_var);
}

void	search_replace(char **str, char *s, char *env_cont, char *env_var)
{
	int i;
	int j;
	int k;
	int flag;
	// char quote_type;
	
	flag = 1;
	i = 0;
	k = 0;
	printf("env_var : %s\n", env_var);
	printf("env_cont : %s\n", env_cont);
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE)
		{
			(*str)[k++] = s[i];
			while (s[++i] && s[i] != SINGLE_QUOTE)
			{
				(*str)[k++] = s[i];
			}
		}
		// printf("i : %d\n", i);
		// printf("strncmp (%s) : (%s) | len : %zu\n", s + i, env_var, ft_strlen(env_var));
		if (!ft_strncmp(s + i, env_var, ft_strlen(env_var)) && flag == 1)
		{
			j = 0;
			while (env_cont[j])
				(*str)[k++] = env_cont[j++];
			flag = 0;
			// while (s[i] != ' ' && !if_quotes(s[i]) && s[i] && ft_isalnum(s[i]))
				// i++;
			i += ft_strlen(env_var);
		}
		if (s[i] == '\0')
			break ;
		// printf("copy s[%d] : %c\n", i, s[i]);
		else
		{
		(*str)[k++] = s[i];
		i++;
		}
		
	}
	(*str)[k] = '\0';
}

char	*replace_sign(char *splitted, int start, t_env *env_table)
{
	int		i;
	char	*env_cont;
	char	*env_var;
	char	*str;

	i = 0;
	env_var = find_env_var(splitted, start);
	// printf("env_var : %s\n", env_var);
	env_cont = find_env_cont(splitted, start, env_table, &str);
	// printf("env_cont : %s\n", env_cont);
	search_replace(&str, splitted, env_cont, env_var);
	// printf("str : %s\n", str);
	free (splitted);
	free (env_cont);
	free (env_var);
	return (str);
}

void	handle_dollarsign(char **splitted, t_env *env_table)
{
	int	i;
	int	j;

	i = -1;
	while (splitted[++i])
	{
		// printf("$split[%d] : %s\n", i, splitted[i]);
		j = 0;
		while (splitted[i][j])
		{
			// printf("$split[%d][%d] : %c\n", i, j, splitted[i][j]);
			if (splitted[i][j] == SINGLE_QUOTE)
				while (splitted[i][++j] && splitted[i][j] != SINGLE_QUOTE)
					continue;
			if (splitted[i][j] == '$')
			{
				splitted[i] = replace_sign(splitted[i], j, env_table);
				printf("$split replaced [%d] : %s\n", i, splitted[i]);
				j = 0;
				continue ;
			}
			j++;
		}
	}
}

void	search_replace(char **str, char *s, char *env_cont, char *env_var)
{
	int i;
	int j;
	int k;
	int flag;
	char quote_type;
	
	flag = 1;
	i = 0;
	k = 0;
	j = 0;
	printf("env_var : %s\n", env_var);
	printf("env_cont : %s\n", env_cont);

	while (s[i])
	{
		if (if_quotes(s[i]))
		quote_type = s[i];
		j = 0;
		while (s[i])
		{
			// printf("$split[%d][%d] : %c\n", i, j, s[i]);
			if (quote_type == SINGLE_QUOTE)
				while (s[i] && s[i] != SINGLE_QUOTE)
					(*str)[k++] = s[i];
			if (quote_type == DOUBLE_QUOTE)
			{
				while (s[i] && s[i] != DOUBLE_QUOTE)
				{
					if (!ft_strncmp(s + i, env_var, ft_strlen(env_var)) && flag == 1)
					{
						while (env_cont[j])
							(*str)[k++] = env_cont[j++];
						flag = 0;
						i += ft_strlen(env_var);
					}
					(*str)[k++] = s[i];
				}
			}
			break ;
		}
		i++;
	}
	(*str)[k] = '\0';
}

char	*replace_sign(char *splitted, int start, t_env *env_table)
{
	int		i;
	char	*env_cont;
	char	*env_var;
	char	*str;

	i = 0;
	env_var = find_env_var(splitted, start);
	// printf("env_var : %s\n", env_var);
	env_cont = find_env_cont(splitted, start, env_table, &str);
	// printf("env_cont : %s\n", env_cont);
	search_replace(&str, splitted, env_cont, env_var);
	// printf("str : %s\n", str);
	free (splitted);
	free (env_cont);
	free (env_var);
	return (str);
}

void	handle_dollarsign(char **splitted, t_env *env_table)
{
	int	i;
	int	j;
	char	quote_type;

	i = -1;
	
	while (splitted[++i])
	{
		j = 0;
		while (splitted[i][j])
		{	
			if (if_quotes(splitted[i][j]))
			{
				// printf("$split[%d] : %s\n", i, splitted[i]);
				quote_type = splitted[i][j];
				while (splitted[i][j])
				{
					// printf("$split[%d][%d] : %c\n", i, j, splitted[i][j]);
					if (quote_type == SINGLE_QUOTE)
						while (splitted[i][++j] && splitted[i][j] != SINGLE_QUOTE)
							continue;
					if (quote_type == DOUBLE_QUOTE)
					{
						while (splitted[i][++j] && splitted[i][j] != DOUBLE_QUOTE)
						{
							if (splitted[i][j] == '$')
							{
								splitted[i] = replace_sign(splitted[i], j, env_table);
								printf("$split replaced [%d] : %s\n", i, splitted[i]);
								j = 0;
								continue ;
							}
						}
					}
					if (splitted[i][j])
						break ;
				}
			}
			j++;
		}
	}
}