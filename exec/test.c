# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

int main(void)
{
	char *cmds[] =
	{
		"/usr/bin/ls",
		"/usr/bin/grep",
	};
	char *args[][3] =
	{
		{"ls", NULL, NULL},
		{"grep", ".c", NULL},
	};
	int	fd[2];
	pid_t	pid;
	int exit_status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(cmds[0], args[0], NULL);
	}
	exit_status = waitpid(pid, NULL, 0);
	exit_status = WEXITSTATUS(exit_status);
	printf("exit: %d\n", exit_status);
	return (0);
}
