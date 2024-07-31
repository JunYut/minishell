# include "pipe.h"

void	pipex(char *cmds[], char ***args, int fd[][2], int cmd_count)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(fd, i, cmd_count - 1);
			close_fds(fd, cmd_count - 1);
			execve(cmds[i], args[i], NULL);
			perror("execve");
			exit(0);
		}
	}
	close_fds(fd, cmd_count);
	i = -1;
	while (++i < cmd_count + 1)
		wait(NULL);
}

// not redirecting properly
void	redirect(int fd[][2], int i, int pipe_count)
{
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(fd[i][1], STDOUT_FILENO);
}

/*
	First child			: close all fds except fd[0][1] (write end)
	Intermediate childs	: close all fds except fd[i - 1][0] (read end) fd[i][1] (write end)
	Last child			: close all fds except fd[last][0] (read end)
*/
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

void	print_pipe(char **args[])
{
    for (int i = 0; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != NULL; j++) {
            printf("%s", args[i][j]);
			if (args[i])
				printf(" ");
        }
		if (args[i + 1])
			printf("| ");
    }
	printf("\n\n");
}
