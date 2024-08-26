# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

// cat >> out.txt < in.txt
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char *cmd = "/usr/bin/cat";
	char *args[] = {"cat", NULL};
	char *files[] = {"out.txt", "in.txt", NULL};
	pid_t pid;
	int fd;
	int exit_status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(files[0], O_APPEND | O_WRONLY | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		fd = open(files[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		execve(cmd, args, envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}

	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		printf("Success exit[%d]: %d\n", pid, exit_status);
	}
	else
		printf("Fail exit[%d]: %d\n", pid, exit_status);
}
