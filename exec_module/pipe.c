# include "exec.h"

int	pipe_io(int *pipefd[2], int pipe_count, int i)
{
	if (i > 0)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(pipefd[i][1], STDOUT_FILENO);
	close_pipes(pipefd, pipe_count);
	return (0);
}

int	file_io(t_file *file, int file_count)
{
	int	fd;
	int	old_io[2];
	int	i;

	old_io[0] = dup(STDIN_FILENO);
	old_io[1] = dup(STDOUT_FILENO);
	i = -1;
	while (++i < file_count)
	{
		if (file[i].type == T_REDIN)
			fd = open(file[i].file, O_RDONLY);
		else if (file[i].type == T_REDOUT)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file[i].type == T_APPEND)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			dup2(old_io[0], STDIN_FILENO);
			dup2(old_io[1], STDOUT_FILENO);
			printf("%s: %s\n", file[i].file, strerror(errno));
			return (-1);
		}
		if (file[i].type == T_REDIN)
			dup2(fd, STDIN_FILENO);
		else if (file[i].type == T_REDOUT || file[i].type == T_APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	open_pipes(int *pipefd[2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("debug");
			return (-1);
		}
	}
	return (0);
}

int	close_pipes(int *pipefd[2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	return (0);
}
