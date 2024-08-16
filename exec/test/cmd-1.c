# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

// cat -e < run.sh < ../define.h | tail -7 > 1.txt > 2.txt > out.txt
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char	*cmd[] =
	{
		"/usr/bin/cat",
		"/usr/bin/tail"
	};
	char	*args[][3] =
	{
		{"cat", "-e", NULL},
		{"tail", "-7", NULL}
	};
	char	*files[][4] =
	{
		{"run.sh", "../define.h", NULL, NULL},
		{"1.txt", "2.txt", "out.txt", NULL}
	};
	pid_t	pid[2];
	int		pipefd[2];
	int		fd;
	int		exit_status[2];

	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		fd = open(files[0][0], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		fd = open(files[0][1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd[0], args[0], envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(pipefd[1]);
		fd = open(files[1][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		fd = open(files[1][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		fd = open(files[1][2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execve(cmd[1], args[1], envp);
		perror("tail");
		exit(EXIT_FAILURE);
	}

	close(pipefd[0]);
	close(pipefd[1]);

	for (int i = 0; i < 2; i++)
	{
		waitpid(pid[i], &exit_status[i], 0);
		if (WIFEXITED(exit_status[i]))
		{
			exit_status[i] = WEXITSTATUS(exit_status[i]);
			printf("Success exit[%d]: %d\n", pid[i], exit_status[i]);
		}
		else
			printf("Fail exit[%d]: %d\n", pid[i], exit_status[i]);
	}
}
