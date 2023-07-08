/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:55:52 by jyim              #+#    #+#             */
/*   Updated: 2023/07/08 11:29:39 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_env *env_table, char **str)
{
	char	*cwd;

	(void)str;
	(void)env_table;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
