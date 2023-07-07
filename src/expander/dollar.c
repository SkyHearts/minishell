/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:26:35 by jyim              #+#    #+#             */
/*   Updated: 2023/06/30 09:54:33 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* 
Base on the $var, find the content.
If $?, return the exit status of last function ran.
If $var, search through environment variable and return correct content.
If $var does not exit, return an empty string
Function also malloc the correct size when $var is expanded.
 */
char	*exit_status(t_env *env_table, char *env_var, int size, char **str)
{
	char	*err_num;

	err_num = ft_itoa(env_table->errnumber);
	(*str) = (char *)malloc (sizeof(char) * (size + ft_strlen(err_num) + 1));
	return (free(env_var), err_num);
}

char	*find_env_cont(char *s, int st, t_env *env, char **str)
{
	int		i;
	int		ed;
	char	*var;
	int		off;

	i = -1;
	ed = st++;
	while (s[++ed] && ft_isalnum_q(s[ed]) && !if_quotes(s[ed]))
		continue ;
	var = ft_substr(s, st, ed - st);
	off = ft_strlen(var);
	if (!ft_strcmp(var, "?"))
		return (exit_status(env, var, (ft_strlen(s) - (ed - st + 1)), str));
	while (env->env[++i])
	{	
		if (!ft_strncmp(var, (env->env[i]), off) && env->env[i][off] == '=')
		{
			(*str) = (char *)malloc (sizeof(char) * (ft_strlen(s)
						- (ed - st + 1) + ft_strlen(env->env[i] + off) + 1));
			return (free(var), ft_strdup(env->env[i] + off + 1));
		}
	}
	(*str) = (char *)malloc (sizeof(char) * (ft_strlen(s)
				- (ed - st + 1) + 1));
	return (free(var), ft_strdup(""));
}

/* 
Find and returns the environment variable located inside the string
 */
char	*find_env_var(char *s, int start)
{
	int		i;
	int		end;
	char	*env_var;

	i = -1;
	end = start;
	while (s[++end] && !if_quotes(s[end]) && ft_isalnum_q(s[end]))
		continue ;
	env_var = ft_substr(s, start, end - start);
	return (env_var);
}

/* 
Replaces the $var while keeping other parts of the string
 */
char	*replace_sign(char *splitted, int start, t_env *env_table)
{
	int		i;
	char	*env_cont;
	char	*env_var;
	char	*str;

	i = 0;
	env_var = find_env_var(splitted, start);
	env_cont = find_env_cont(splitted, start, env_table, &str);
	str = ft_strncpy(str, splitted, start);
	str = ft_strcat(str, env_cont);
	str = ft_strcat(str, splitted + ft_strlen(env_var) + start);
	free(splitted);
	free(env_cont);
	free(env_var);
	return (str);
}

/* 
Search through the splitted string one by one and replaces the $var
one by one with it's content
Example: "$USER is $USER not" '$USER'
1st Iter : "jyim is $USER not" '$USER'
Last Iter : "jyim is jyim not" '$USER'
 */
void	handle_dollarsign(char **split, t_env *env_table, int hdoc)
{
	int			i;
	int			j;
	static char	quote_type;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (if_quotes(split[i][j]))
				quote_type = split[i][j];
			if (split[i][j] == SINGLE_QUOTE && !hdoc)
				while (split[i][++j] && split[i][j] != SINGLE_QUOTE)
					continue ;
			if (split[i][j] == DOUBLE_QUOTE && !hdoc)
				while (split[i][++j] && split[i][j] != DOUBLE_QUOTE)
					if (split[i][j] == '$')
						split[i] = replace_sign(split[i], j, env_table);
			if (split[i][j] == '$')
				split[i] = replace_sign(split[i], j, env_table);
			if (split[i][j] == '\0')
				break ;
		}
	}	
}
