/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:35 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 20:04:03 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_func(t_env *env_table, int *ret, char **env)
{
	(*ret) = 0;
	env_table->path = NULL;
	env_table->func[E_ECHO] = ft_echo;
	env_table->func[E_CD] = ft_cd;
	env_table->func[E_PWD] = ft_pwd;
	env_table->func[E_EXPORT] = ft_export;
	env_table->func[E_UNSET] = ft_unset;
	env_table->func[E_ENV] = ft_env;
	env_table->func[E_EXIT] = ft_exit;
	env_table->functions = ft_split("echo cd pwd export unset env exit", ' ');
	env_table->errnumber = 0;
	env_table->rl_buffer = NULL;
	env_table->hdoc = NULL;
	env_table->env = dup_env(env);
}

char	*insert_line(char *input, t_env *env_table)
{
	char	*nextline;
	char	*new_input;
	char	*rstr;

	(void)env_table;
	rstr = NULL;
	nextline = readline(">");
	if (!nextline)
		return (NULL);
	new_input = ft_strjoin(input, "\n");
	rstr = ft_strjoin(new_input, nextline);
	free(input);
	free(nextline);
	free(new_input);
	return (rstr);
}

//123456789101112 13 14
//echo hell o _ | _   /0
char	*handle_last_pipe(char *input)
{
	int		i;
	char	*next;
	char	*rstr;

	i = ft_strlen(input);
	i -= 1;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '|')
	{
		rstr = ft_strjoin_f(input, " ");
		while (1)
		{
			next = readline(">");
			if (!next)
				return (NULL);
			rstr = ft_strjoin_f(rstr, next);
			if (!isempty(next))
				break ;
			free(next);
		}
		return (free(next), rstr);
	}
	return (input);
}

char	*read_input(t_env *env_table)
{
	char	*input;

	init_signal();
	input = readline("minishell> ");
	if (input == NULL)
		return (ft_strdup("exit"));
	while (check_quotes(input))
			input = insert_line(input, env_table);
	if (!ft_strcmp(input, ""))
		return (input);
	if (!is_onlypipe(input))
		input = handle_last_pipe(input);
	add_history(input);
	input = expand_operators(input);
	reduce_white_spaces_3(input);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_env		env_table;
	char		*input;
	int			ret;

	(void)argc;
	(void)argv;
	init_func(&env_table, &ret, env);
	while (1)
	{
		input = read_input(&env_table);
		if (isempty(input) || parse_cmds(input, &env_table))
		{
			free(input);
			continue ;
		}
		ret = ft_pipe(&env_table, env_table.env);
		free(input);
		if (ret > 0)
			env_table.errnumber = ret;
		if (ret == -2)
			break ;
		free_var(&env_table);
	}
	free_all(&env_table);
	return (system("leaks -q minishell"), 0);
}

			//printf("=========CMDGROUPS=============\n");
			//int m = -1;
			//while (++m < env_table.nos_pipe)
			//{
			//	int k = -1;
			//	while (env_table.cmdgroups[m].args
			//			&& env_table.cmdgroups[m].args[++k])
			//		printf("cmdgroups[%d][%d]: [%s]$\n", m,
			//			k, env_table.cmdgroups[m].args[k]);
			//	k = -1;
			//	while (env_table.cmdgroups[m].rdr_info
			//			&& env_table.cmdgroups[m].rdr_info[++k].rdr_str)
			//	{
			//		printf("cmdgroups[%d][%d]rdrstr: [%s]$\n", m,
			//			k, env_table.cmdgroups[m].rdr_info[k].rdr_str);
			//		printf("cmdgroups[%d][%d]rdrtype: [%d]$\n", m,
			//			k, env_table.cmdgroups[m].rdr_info[k].rdr_type);
			//	}
			//}
			//printf("===============================\n");