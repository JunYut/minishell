# include "pipe.h"

void	pipex(char *cmds[], char ***args, int fd[][2], int pipe_count)
{
	pid_t	pid;
	int		i;

	(void)cmds;
	(void)args;
	(void)fd;
	(void)pipe_count;
	i = -1;
	while (++i < pipe_count + 1)
	{
		pid = fork();
		if (pid == 0)
		{
			// printf("child [%d]: %d\n", i, getpid());
			// close_fds(fd, i, pipe_count);
			redirect(fd, i, pipe_count);
			// execve(cmds[i], args[i], NULL);
			exit(0);
		}
	}
	wait(NULL);
}

// not redirecting properly
void	redirect(int fd[][2], int i, int pipe_count)
{
	int	stdout_fd;
	int	stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	if (i == pipe_count)
		return ;
	// printf("i: %d\n", i);
	// printf("redirecting\n");
	if (i == 0)
		dup2(fd[0][1], STDOUT_FILENO);
	else if (i == pipe_count - 1)
		dup2(fd[pipe_count - 1][0], STDIN_FILENO);
	else
	{
		// printf("redirecting both\n");
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdout_fd);
	close(stdin_fd);
	// printf("redirected\n");
}

// i is the index of the current pipe
void	close_fds(int fd[][2], int i, int pipe_count)
{
	int	j;

	// printf("i: %d\n", i);
	// printf("closing fds\n");
	if (i == 0)
		close(fd[0][0]);
	// printf("closed fd[0][0]\n");
	j = -1;
	while (++j < pipe_count)
	{
		if (i > 0 && j > 0)
			close(fd[j - 1][1]);
		close(fd[j][0]);
	}
	// printf("closed most fds\n");
	if (i == pipe_count - 1)
		close(fd[pipe_count - 1][1]);
	// printf("closed all fds\n");
}
