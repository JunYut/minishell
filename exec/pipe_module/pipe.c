# include "pipe.h"

// cmds: array of full path to commands, NULL terminated
// argv: array of arguments for each command, NULL terminated
void	pipex(char *cmds[], char ***argv, int fd[][2], int cmd_count)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			redir_io(fd, i, cmd_count - 1);
			close_fds(fd, cmd_count - 1);
			execve(cmds[i], argv[i], NULL);
			perror("execve");
			exit(0);
		}
	}
	close_fds(fd, cmd_count);
	i = -1;
	while (++i < cmd_count + 1)
		wait(NULL);
}

int	*pipe_o(void)
{
	int	*fds;

	fds = malloc(4 * sizeof(int));
	fds[3] = dup(STDOUT_FILENO);
	fds[2] = dup(STDIN_FILENO);
	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(0);
	}
	dup2(fds[1], STDOUT_FILENO);
	dup2(fds[0], STDIN_FILENO);
	return (fds);
}

int	pipe_c(int pipefd[2], int stdio_fd[2])
{
	close(pipefd[1]);
	dup2(stdio_fd[1], STDOUT_FILENO);
	close(stdio_fd[1]);
	close(pipefd[0]);
	dup2(stdio_fd[0], STDIN_FILENO);
	close(stdio_fd[0]);
	return (0);
}

void	redir_io(int fd[][2], int i, int pipe_count)
{
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(fd[i][1], STDOUT_FILENO);
}

void	close_fds(int fd[][2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	print_pipe(char **argv[])
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			printf("%s", argv[i][j]);
			if (argv[i])
				printf(" ");
		}
		if (argv[i + 1])
			printf("| ");
	}
	printf("\n\n");
}
