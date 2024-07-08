# include "pipe.h"

void	pipex(char *cmds[], char ***args, int **fd, int pipe_count)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < pipe_count)
	{
		pid = fork();
		if (pid == 0)
		{
			close_fds(fd, i, pipe_count);
			redirect(fd, i, pipe_count);
			execve(cmds[i], args[i], NULL);
		}
	}
}

void	redirect(int **fd, int i, int pipe_count)
{
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == pipe_count - 1)
		dup2(fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
}

// i is the index of the current pipe
void	close_fds(int **fd, int i, int pipe_count)
{
	int	j;

	if (i == 0)
		close(fd[i][0]);
	j = -1;
	while (++j <= i)
	{
		if (i > 0)
			close(fd[j - 1][1]);
		close(fd[j][0]);
	}
	if (i == pipe_count - 1)
		close(fd[i][1]);
}
