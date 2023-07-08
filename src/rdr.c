/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:06:03 by sulim             #+#    #+#             */
/*   Updated: 2023/07/08 12:10:46 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pipe_hdoc(int index, char **hdoc)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(1);
	write(fd[1], hdoc[index], ft_strlen(hdoc[index]));
	close(fd[1]);
	return (fd[0]);
}

void	openfile(int index, int rdrfiles[2], char **hdoc, t_rdrinfo rdrinfo)
{
	if (rdrinfo.rdr_type == IN || rdrinfo.rdr_type == HEREDOC)
	{
		if (rdrfiles[0] != -1)
			close(rdrfiles[0]);
		if (rdrinfo.rdr_type == IN)
			rdrfiles[0] = open(rdrinfo.rdr_str, O_RDONLY);
		else if (rdrinfo.rdr_type == HEREDOC)
			rdrfiles[0] = pipe_hdoc(index, hdoc);
		if (rdrfiles[0] < 0)
			error(ERR_FILE);
	}
	else if (rdrinfo.rdr_type == OUT || rdrinfo.rdr_type == APPEND)
	{
		if (rdrfiles[1] != -1)
			close (rdrfiles[1]);
		if (rdrinfo.rdr_type == OUT)
			rdrfiles[1] = open(rdrinfo.rdr_str, O_TRUNC | O_CREAT | O_RDWR, \
			S_IRWXU | S_IRGRP | S_IROTH);
		else if (rdrinfo.rdr_type == APPEND)
			rdrfiles[1] = open(rdrinfo.rdr_str, O_APPEND | O_CREAT | O_RDWR, \
			S_IRWXU | S_IRGRP | S_IROTH);
		if (rdrfiles[1] < 0)
			error(ERR_FILE);
	}
}

void	check_rdr(int index, char **hdoc, t_pipe pipe, int rdrfiles[2])
{
	int	count;

	rdrfiles[0] = -1;
	rdrfiles[1] = -1;
	count = -1;
	while (++count < pipe.rdr_count)
		openfile(index, rdrfiles, hdoc, pipe.rdr_info[count]);
	if (rdrfiles[0] != -1)
		ft_dup(rdrfiles[0], STDIN_FILENO);
	if (rdrfiles[1] != -1)
		ft_dup(rdrfiles[1], STDOUT_FILENO);
	close(rdrfiles[0]);
	close(rdrfiles[1]);
}
