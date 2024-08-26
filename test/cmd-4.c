# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

# define TEST 1

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char *cmd[] =
	{
		"/usr/bin/cat",
		"/usr/bin/grep",
		"/usr/bin/tr"
	};
	pid_t pid[3];
	int pipefd[2][2];
	int exit_status[3];
	// cat -e < ../../TODO | grep command | tr o u > out.txt
	# if TEST == 1
	char *args[][4] =
	{
		{"cat", "-e", NULL, NULL},
		{"grep", "command", NULL, NULL},
		{"tr", "o", "u", NULL}
	};
	int fd;

	pipe(pipefd[0]);
	pipe(pipefd[1]);
	pid[0] = fork();
	if (pid[0] == 0)	// cat -e < ../../TODO
	{
		fd = open("../../TODO", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		dup2(pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][1]);
		execve(cmd[0], args[0], envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}
	pid[1] = fork();
	if (pid[1] == 0)	// grep command
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		execve(cmd[1], args[1], envp);
		perror("grep");
		exit(EXIT_FAILURE);
	}
	pid[2] = fork();
	if (pid[2] == 0)	// tr o u
	{
		fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][1]);
		dup2(pipefd[1][0], STDIN_FILENO);
		close(pipefd[1][0]);
		execve(cmd[2], args[2], envp);
		perror("tr");
		exit(EXIT_FAILURE);
	}
	# endif
	// cat -e ../../TODO | grep command | tr o u
	# if TEST == 2
	char *args[][4] =
	{
		{"cat", "-e", "../../TODO", NULL},
		{"grep", "command", NULL, NULL},
		{"tr", "o", "u", NULL}
	};

	pipe(pipefd[0]);
	pipe(pipefd[1]);
	pid[0] = fork();
	if (pid[0] == 0)	// cat -e ../../TODO
	{
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		dup2(pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][1]);
		execve(cmd[0], args[0], envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}
	pid[1] = fork();
	if (pid[1] == 0)	// grep command
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		execve(cmd[1], args[1], envp);
		perror("grep");
		exit(EXIT_FAILURE);
	}
	pid[2] = fork();
	if (pid[2] == 0)	// tr o u
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][1]);
		dup2(pipefd[1][0], STDIN_FILENO);
		close(pipefd[1][0]);
		execve(cmd[2], args[2], envp);
		perror("tr");
		exit(EXIT_FAILURE);
	}
	# endif

	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);

	for (int i = 0; i < 3; i++)
	{
		waitpid(pid[i], &exit_status[i], 0);
		if (WIFEXITED(exit_status[i]))
		{
			exit_status[i] = WEXITSTATUS(exit_status[i]);
			printf("exit status: %d\n", exit_status[i]);
		}
		else
			printf("exit status: %d\n", exit_status[i]);
	}
}
