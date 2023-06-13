void parent()
{

}

void child()
{

}

void ft_pipex(char *input, t_pipex *pipex)
{
	if (pipex.pid == 0)
		child(input);
	else
		parent(input);
}