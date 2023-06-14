/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:35 by jyim              #+#    #+#             */
/*   Updated: 2023/06/14 17:27:30 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_func(t_env *env_table)
{
	env_table->func[E_ECHO] = ft_echo;
	// env_table->func[E_CD] = func_cd;
	// env_table->func[E_PWD] = func_pwd;
	// env_table->func[E_EXPORT] = func_export;
	// env_table->func[E_UNSET] = func_unset;
	// env_table->func[E_ENV] = func_env;
	// env_table->func[E_EXIT] = func_exit;
}

void	print_darray(char **array)
{
	int i = 0;

	printf("--------Double array--------\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("----------------------------\n");
}

// /* To read, reduce and expand input before parsing */
char *read_input(void)
{
	char *input;

	input = readline("minishell> ");
	if (input == NULL)
		exit_error();
	while (check_quotes(input))
			input = insert_line(input);
	add_history(input);
	// printf("Input: %s\n", input);
	input = reduce_white_spaces(input);
	input = expand_operators(input);
	// printf("Input After Expand: %s$\n", input);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_env		env_table;
	char		*input;
	int 		ret;

	env_table.env = dup_env(env);
	env_table.path = extract_path(env_table.env);
	(void)argc;
	(void)argv;
	init_func(&env_table);
	// print_darray(env_table.env);
	print_darray(env_table.path);
	while (1)
	{
		input = read_input();
		if (!ft_strncmp(input, "exit", 5))
			exit(0);
		ret = parse_cmds(input, &env_table);
		// exec_cmds();
		if (ret == 1)
		{
			// free(input);
			continue;
		}
		// printf("=========CMDGROUPS=============\n");
		// int m = -1;
		// while (++m < env_table.nos_pipe)
		// {
		// 	int k = -1;
		// 	while (env_table.cmdgroups[m].args[++k])
		// 		printf("cmdgroups[%d][%d]: %s\n", m, k, env_table.cmdgroups[m].args[k]);
		// }
		// printf("===============================\n");
		// ft_pipe(&env_table, env);
		ft_pipe(&env_table);
	}
}

	// input = reduce_double_operators(input);
	// char s[] = "lets do this! as sad ";
	// char d[] = " ";

	// char *s1 = argv_to_str(argv);
	// printf("%s\n", s1);
	// char *s2 = expand_operators(s1);
	// printf("%s\n", s2);
	// char *s3 = reduce_double_operators(s2);
	// printf("%s\n", s3);

	// char s_op[] = "asd < < asd";

	// int i = 0;
	// while (s_op[i])
	// {
	// 	printf("%d", ft_is_double_operator(s_op, i));
	// 	i++;
	// }

	// for (int i = 0; i < 14 ; i++) 
	// 	if (s[i] == '\0')
	// 		printf("\\0\n");
	// 	else
	// 		printf("%c", s[i]);