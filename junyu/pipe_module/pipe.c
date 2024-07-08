# include "pipe.h"

void	pipex(char *cmds[], char ***args, int **fd, int pipe_count)
{
	pid_t	pid;
	int		i;

	(void)cmds;
	(void)args;
	(void)fd;
	(void)pipe_count;
	(void)pid;
	i = -1;
	while (++i < pipe_count)
	{
		pid = fork();
		if (pid == 0)
		{
			close_fds(fd, i, pipe_count);
			// redirect(fd, i, pipe_count);
			for (int i = 0; fd[i]; i++)
				printf("fd[%d]: %d %d\n", i, fd[i][0], fd[i][1]);
			// execve(cmds[i], args[i], NULL);
		}
	}

	// for (int j = 0; cmds[j]; j++)
	// {
	// 	printf("cmd[%d]: %s ", j, cmds[j]);
	// 	for (int k = 0; args[j][k]; k++)
	// 		printf("%s ", args[j][k]);
	// 	printf("\n");
	// }
}

void	redirect(int **fd, int i, int pipe_count)
{
	printf("redirecting\n");
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == pipe_count - 1)
		dup2(fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	printf("redirected\n");
}

// i is the index of the current pipe
// !!! stuck at while loop !!!
void	close_fds(int **fd, int i, int pipe_count)
{
	int	j;

	printf("i: %d\n", i);
	printf("closing fds\n");
	if (i == 0)
		close(fd[i][0]);
	printf("closed fd[0][0]\n");
	j = -1;
	while (++j <= i)
	{
		if (i > 0 && j > 0)
			close(fd[j - 1][1]);
		close(fd[j][0]);
	}
	printf("closed most fds\n");
	if (i == pipe_count - 1)
		close(fd[i][1]);
	printf("closed all fds\n");
}
