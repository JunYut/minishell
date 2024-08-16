# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

// echo hello | cat -e | tr h H || echo goodbye | cat -e | tr o e && echo wait | cat -e | tr w t
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char	*cmd[] =
	{
		"/bin/echo",
		"/bin/cat",
		"/usr/bin/tr",
		"/bin/echo",
		"/bin/cat",
		"/usr/bin/tr",
		"/bin/echo",
		"/bin/cat",
		"/usr/bin/tr"
	};
	char	*args[][4] =
	{
		{"echo", "hello", NULL, NULL},
		{"cat", "-e", NULL, NULL},
		{"tr", "h", "H", NULL},
		{"echo", "goodbye", NULL, NULL},
		{"cat", "-e", NULL, NULL},
		{"tr", "o", "e", NULL},
		{"echo", "wait", NULL, NULL},
		{"cat", "-e", NULL, NULL},
		{"tr", "w", "t", NULL}
	};
	pid_t	pid[3][3];
	int		pipefd[3][2][2];
	int		exit_status;

	pipe(pipefd[0][0]);
	pipe(pipefd[0][1]);
	pid[0][0] = fork();
	if (pid[0][0] == 0)
	{
		close(pipefd[0][0][0]);
		dup2(pipefd[0][0][1], STDOUT_FILENO);
		close(pipefd[0][0][1]);
		execve(cmd[0], args[0], envp);
		perror("echo");
		exit(EXIT_FAILURE);
	}
	pid[0][1] = fork();
	if (pid[0][1] == 0)
	{
		close(pipefd[0][0][1]);
		dup2(pipefd[0][0][0], STDIN_FILENO);
		close(pipefd[0][0][0]);
		close(pipefd[0][1][0]);
		dup2(pipefd[0][1][1], STDOUT_FILENO);
		close(pipefd[0][1][1]);
		execve(cmd[1], args[1], envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}
	pid[0][2] = fork();
	if (pid[0][2] == 0)
	{
		close(pipefd[0][0][0]);
		close(pipefd[0][0][1]);
		close(pipefd[0][1][1]);
		dup2(pipefd[0][1][0], STDIN_FILENO);
		close(pipefd[0][1][0]);
		execve(cmd[2], args[2], envp);
		perror("tr");
		exit(EXIT_FAILURE);
	}

	close(pipefd[0][0][0]);
	close(pipefd[0][0][1]);
	close(pipefd[0][1][0]);
	close(pipefd[0][1][1]);

	for (int i = 0; i < 3; ++i)
	{
		waitpid(pid[0][i], &exit_status, 0);
		if (WIFEXITED(exit_status))
		{
			exit_status = WEXITSTATUS(exit_status);
			printf("exit status: %d\n", exit_status);
		}
		else
			printf("exit status: %d\n", exit_status);
	}

	if (exit_status == -1)
	{
		pipe(pipefd[1][0]);
		pipe(pipefd[1][1]);
		pid[1][0] = fork();
		if (pid[1][0] == 0)
		{
			close(pipefd[1][0][0]);
			dup2(pipefd[1][0][1], STDOUT_FILENO);
			close(pipefd[1][0][1]);
			execve(cmd[3], args[3], envp);
			perror("echo");
			exit(EXIT_FAILURE);
		}
		pid[1][1] = fork();
		if (pid[1][1] == 0)
		{
			close(pipefd[1][0][1]);
			dup2(pipefd[1][0][0], STDIN_FILENO);
			close(pipefd[1][0][0]);
			close(pipefd[1][1][0]);
			dup2(pipefd[1][1][1], STDOUT_FILENO);
			close(pipefd[1][1][1]);
			execve(cmd[4], args[4], envp);
			perror("cat");
			exit(EXIT_FAILURE);
		}
		pid[1][2] = fork();
		if (pid[1][2] == 0)
		{
			close(pipefd[1][0][0]);
			close(pipefd[1][0][1]);
			close(pipefd[1][1][1]);
			dup2(pipefd[1][1][0], STDIN_FILENO);
			close(pipefd[1][1][0]);
			execve(cmd[5], args[5], envp);
			perror("tr");
			exit(EXIT_FAILURE);
		}

		close(pipefd[1][0][0]);
		close(pipefd[1][0][1]);
		close(pipefd[1][1][0]);
		close(pipefd[1][1][1]);

		for (int i = 0; i < 3; ++i)
		{
			waitpid(pid[1][i], &exit_status, 0);
			if (WIFEXITED(exit_status))
			{
				exit_status = WEXITSTATUS(exit_status);
				printf("exit status: %d\n", exit_status);
			}
			else
				printf("exit status: %d\n", exit_status);
		}
	}

	if (exit_status == 0)
	{
		pipe(pipefd[2][0]);
		pipe(pipefd[2][1]);
		pid[2][0] = fork();
		if (pid[2][0] == 0)
		{
			close(pipefd[2][0][0]);
			dup2(pipefd[2][0][1], STDOUT_FILENO);
			close(pipefd[2][0][1]);
			execve(cmd[6], args[6], envp);
			perror("echo");
			exit(EXIT_FAILURE);
		}
		pid[2][1] = fork();
		if (pid[2][1] == 0)
		{
			close(pipefd[2][0][1]);
			dup2(pipefd[2][0][0], STDIN_FILENO);
			close(pipefd[2][0][0]);
			close(pipefd[2][1][0]);
			dup2(pipefd[2][1][1], STDOUT_FILENO);
			close(pipefd[2][1][1]);
			execve(cmd[7], args[7], envp);
			perror("cat");
			exit(EXIT_FAILURE);
		}
		pid[2][2] = fork();
		if (pid[2][2] == 0)
		{
			close(pipefd[2][0][0]);
			close(pipefd[2][0][1]);
			close(pipefd[2][1][1]);
			dup2(pipefd[2][1][0], STDIN_FILENO);
			close(pipefd[2][1][0]);
			execve(cmd[8], args[8], envp);
			perror("tr");
			exit(EXIT_FAILURE);
		}

		close(pipefd[2][0][0]);
		close(pipefd[2][0][1]);
		close(pipefd[2][1][0]);
		close(pipefd[2][1][1]);

		for (int i = 0; i < 3; ++i)
		{
			waitpid(pid[2][i], &exit_status, 0);
			if (WIFEXITED(exit_status))
			{
				exit_status = WEXITSTATUS(exit_status);
				printf("exit status: %d\n", exit_status);
			}
			else
				printf("exit status: %d\n", exit_status);
		}
	}
}
