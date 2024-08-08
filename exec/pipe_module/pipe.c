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
