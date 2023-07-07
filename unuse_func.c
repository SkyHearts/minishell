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

/* 
// Copy the original string up to the insertion position
// Insert the space
// Copy the remaining characters from the original string
// Add the null terminator
// Free the original string
// Return the modified string
// Failed to allocate memory, return the original string
 */
char	*add_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (new_str != NULL)
	{
		ft_strncpy(new_str, str, pos);
		new_str[pos] = ' ';
		ft_strncpy(new_str + pos + 1, str + pos, len - pos);
		new_str[len + 1] = '\0';
		free(str);
		return (new_str);
	}
	else
		return (str);
}

/* 
// Copy the original string up to the remove space position
// Copy the remaining characters from the original string
// Add the null terminator
// Free the original string
// Return the modified string
// Failed to allocate memory, return the original string
 */
char	*reduce_space(char *str, size_t len, size_t pos)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (len));
	if (new_str != NULL)
	{
		ft_strncpy(new_str, str, pos);
		ft_strncpy(new_str + pos, str + pos + 1, len - pos - 1);
		new_str[len - 1] = '\0';
		free(str);
		return (new_str);
	}
	else
		return (str);
}

char	*expand_str(char *s, int i)
{
	if (s[i + 1] != ' ' && !ft_char_cmp_str(s[i + 1], OPERATORS)
		&& !if_quotes(s[i + 1]) && s[i + 1])
		s = add_space(s, ft_strlen(s), i + 1);
	if (i > 0)
	{
		if (if_quotes(s[i - 1]) && s[i] == '|')
			s = add_space(s, ft_strlen(s), i);
		else if (if_quotes(s[i - 1]) && ft_char_cmp_str(s[i - 1], "\"'"))
			s = add_space(s, ft_strlen(s), i);
		else if (s[i - 1] != ' ' && !ft_char_cmp_str(s[i - 1], OPERATORS)
			&& !if_quotes(s[i - 1]))
			s = add_space(s, ft_strlen(s), i);
	}
	return (s);
}

/* 
Function adds whitespace to locations with OPERATORS and QUOTES using the
expand_str function.
Example : echo hello|wc -> echo hello | wc
 */
char	*expand_operators(char *s)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = -1;
	while (s[i])
	{
		if (if_quotes(s[i]))
		{
			quote_type = s[i++];
			while (s[i] && s[i] != quote_type)
				i++;
		}
		else if (s[i] == PIPE)
			s = expand_str(s, i);
		else if (s[i] == REDIRECT_LEFT)
			s = expand_str(s, i);
		else if (s[i] == REDIRECT_RIGHT)
			s = expand_str(s, i);
		i++;
	}
	return (s);
}