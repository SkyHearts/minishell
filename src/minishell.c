/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:35 by jyim              #+#    #+#             */
/*   Updated: 2023/06/06 10:48:25 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	t_env		env_table;
	t_cmd		*cmdgroups;
	char		*input;

	env_table.env = dup_env(env);
	env_table.path = extract_path(env_table.env);
	print_darray(env_table.env);
	print_darray(env_table.path);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit_error();
		else if (!ft_strncmp(input, "exit", 5))
			exit(0);
		else
		{
			while (check_quotes(input))
				input = insert_line(input);
			add_history(input);
			printf("Input: %s\n", input);
			// print_darray(env);
			printf("Input if using ft_strtrim: %s$\n", ft_strtrim(input, " "));
			input = reduce_white_spaces(input);
			input = expand_operators(input);
			printf("Input After Expand: %s$\n", input);
			parse_cmds(input, cmdgroups);
		}
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