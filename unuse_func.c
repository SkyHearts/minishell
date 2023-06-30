// int	ft_is_double_operator(char *s, int i)
// {
// 	if(s[i] == ' ')
// 		if (ft_str_cmp_str(s[i - 1], OPERATORS) && ft_str_cmp_str(s[i + 1], OPERATORS))
// 			return (1);
// 	return (0);
// }

// char	*reduce_double_operators(char *s)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (ft_is_double_operator(s, i))
// 			s = reduce_space(s, ft_strlen(s), i);
// 		i++;
// 	}
// 	return (s);
// }

// char	*find_env_cont(char *splitted, int start, t_env *env_table, char **str)
// {
// 	int		i;
// 	int		end;
// 	char	*env_var;
// 	int		offset;
// 	char	*err_num;
	
// 	i = -1;
// 	end = start++;
// 	while (splitted[++end] && ft_isalnum_q(splitted[end]) && !if_quotes(splitted[end]))
// 		continue ;
// 	env_var = ft_substr(splitted, start, end - start);
// 	offset = ft_strlen(env_var);
// 	if (!ft_strcmp(env_var, "?"))
// 	{
// 		err_num = ft_itoa(env_table->errnumber);
// 		(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
// 					+ ft_strlen(err_num) + 1));
// 		return (free(env_var), err_num);
// 	}
// 	while (env_table->env[++i])
// 	{	
// 		if (!ft_strncmp(env_var, (env_table->env[i]), offset) && env_table->env[i][offset] == '=')
// 		{
// 			(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
// 					+ ft_strlen(env_table->env[i] + offset) + 1));
// 			return (free(env_var), ft_strdup(env_table->env[i] + offset + 1));
// 		}
// 	}
// 	(*str) = (char *)malloc (sizeof(char) * (ft_strlen(splitted) - (end - start + 1)
// 					 + 1));
// 	if (!(*str))
// 		printf("Malloc failed");
// 	return (free(env_var), ft_strdup(""));
// }

// char	*find_env_var(char *s, int start)
// {
// 	int		i;
// 	int		end;
// 	char	*env_var;

// 	i = -1;
// 	end = start;
// 	while (s[++end] && !if_quotes(s[end]) && ft_isalnum_q(s[end]))
// 		continue ;
// 	env_var = ft_substr(s, start, end - start);
// 	return (env_var);
// }

// char	*replace_sign(char *splitted, int start, t_env *env_table)
// {
// 	int		i;
// 	char	*env_cont;
// 	char	*env_var;
// 	char	*str;

// 	i = 0;
// 	env_var = find_env_var(splitted, start);
// 	env_cont = find_env_cont(splitted, start, env_table, &str);
// 	str = ft_strncpy(str, splitted, start);
// 	str = ft_strcat(str, env_cont);
// 	str = ft_strcat(str, splitted + ft_strlen(env_var) + start);
// 	free(splitted);
// 	free(env_cont);
// 	free(env_var);
// 	return (str);
// }

// void	handle_dollarsign(char **splitted, t_env *env_table)
// {
// 	int	i;
// 	int	j;
// 	char quote_type;

// 	i = -1;
// 	quote_type = '\0';
// 	while (splitted[++i])
// 	{
// 		j = -1;
// 		while (splitted[i][++j])
// 		{
// 			if (if_quotes(splitted[i][j]))
// 			{
// 				quote_type = splitted[i][j];
// 				if (splitted[i][j] == SINGLE_QUOTE)
// 				{
// 					while (splitted[i][++j] && splitted[i][j] != SINGLE_QUOTE)
// 						continue ;
// 				}
// 				if (splitted[i][j] == DOUBLE_QUOTE)
// 				{
// 					while (splitted[i][++j] && splitted[i][j] != DOUBLE_QUOTE)
// 					{
// 						if (splitted[i][j] == '$')
// 							splitted[i] = replace_sign(splitted[i], j, env_table);
// 					}
// 				}
// 			}
// 			if (splitted[i][j] == '$')
// 				splitted[i] = replace_sign(splitted[i], j, env_table);
// 			if (splitted[i][j] == '\0')
// 				break ;
// 		}
// 	}	
// }

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