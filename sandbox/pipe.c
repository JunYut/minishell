# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define PROGRAM 4
# define CMD_COUNT 3
# define PIPE_COUNT CMD_COUNT - 1
# define BUFFER_SIZE 4096

char	*read_pipe(int read_fd);
void	append_str(char **str1, char *str2);

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;

	// Single pipe
	// env | grep PWD
	# if PROGRAM == 0
		int fd[2];
		pid_t pid;

		pipe(fd);	// write: fd[1], read: fd[0]
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]); // close read end
			dup2(fd[1], 1); // stdout -> fd[1]
			execve("/usr/bin/env", (char *[]){"env", NULL, NULL}, envp);
		}
		close(fd[1]); // close write end
		dup2(fd[0], 0); // stdout -> fd[0]
		char *args[] = {"grep", "PWD", NULL};
		execve("/usr/bin/grep", args, envp);
	# endif
	// 2 pipes
	# if PROGRAM == 1
		char *cmds[] =
		{
			"/usr/bin/ls",
			"/usr/bin/grep",
			"/usr/bin/wc"
		};
		char *args[][3] =
		{
			{"ls", NULL, NULL},
			{"grep", ".c", NULL},
			{"wc", "-l", NULL}
		};
		int fd[2][2];
		pid_t pid;

		pipe(fd[0]);
		pipe(fd[1]);

		pid = fork();
		if (pid == 0)
		{
			close(fd[0][0]); // not used
			close(fd[1][0]); // not used
			close(fd[1][1]); // not used
			dup2(fd[0][1], 1); // stdout -> fd[1]
			execve(cmds[0], args[0], NULL);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				close(fd[0][1]); // not used
				close(fd[1][0]); // not used
				dup2(fd[0][0], 0); // stdin -> fd[0]
				dup2(fd[1][1], 1); // stdout -> fd[1]
				execve(cmds[1], args[1], NULL);
			}
			else
			{
				close(fd[0][0]); // not used
				close(fd[0][1]); // not used
				close(fd[1][1]); // not used
				dup2(fd[1][0], 0); 	// Causing infinite loop
				execve(cmds[2], args[2], NULL);
			}
		}

	# endif
	// 3 pipes
	# if PROGRAM == 2
	char *cmds[] =
	{
		"/bin/ls",
		"/usr/bin/grep",
		"/usr/bin/sort",
		"/bin/cat",
		NULL
	};
	char **args[] =
	{
		(char *[]){"ls", NULL},
		(char *[]){"grep", "c", NULL},
		(char *[]){"sort", "-r", NULL},
		(char *[]){"cat", "-e", NULL},
		NULL
	};
	int	fd[3][2];
	pid_t pid;

	printf("PID: %d\n", getpid());

	for (int i = 0; i < 3; i++)
		pipe(fd[i]);

	pid = fork();
	if (pid == 0)
	{
		close(fd[0][0]);
		close(fd[1][0]);
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[2][1]);
		dup2(fd[0][1], STDOUT_FILENO);
		execve(cmds[0], args[0], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		dup2(fd[0][0], STDIN_FILENO);
		dup2(fd[1][1], STDOUT_FILENO);
		execve(cmds[1], args[1], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		dup2(fd[1][0], STDIN_FILENO);
		dup2(fd[2][1], STDOUT_FILENO);
		execve(cmds[2], args[2], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		close(fd[2][1]);
		dup2(fd[2][0], STDIN_FILENO);
		execve(cmds[3], args[3], envp);
	}
	wait(NULL);
	# endif
	// Error tests
	# if PROGRAM == 3
	char *cmds[] =
	{
		"/usr/bin/head",
		"/usr/bin/tr"
	};
	char *args[][4] =
	{
		{"head", NULL},
		{"tr", "-c", "\'[:alnum:]\'", NULL}
	};
	int fd[2];

	pipe(fd);
	dup2(fd[1], 0); // head: Error reading stdin
	// dup2(fd[0], 1);

	execve(cmds[1], args[1], envp);
	# endif
	// cat < ../TODO | grep command | wc -l && echo "Done" > ../out.txt
	# if PROGRAM == 4
	char	*cmds[] =
	{
		"/bin/cat",
		"/usr/bin/grep",
		"/usr/bin/wc",
		"/bin/echo"
	};
	char	*argv[][4] =
	{
		{"cat", NULL},
		{"grep", "command", NULL},
		{"wc", "-l", NULL},
		{"echo", "Done", NULL}
	};
	pid_t pid;
	int	fd;
	int pipefd[2][2];

	for (int i = 0; i < 2; i++)
		pipe(pipefd[i]);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		fd = open("../TODO", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[0][1], STDOUT_FILENO);
		execve(cmds[0], argv[0], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		execve(cmds[1], argv[1], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][1]);
		dup2(pipefd[1][0], STDIN_FILENO);
		execve(cmds[2], argv[2], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		fd = open("../out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		execve(cmds[3], argv[3], envp);
	}
	# endif
}

char	*read_pipe(int read_fd)
{
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = malloc(1);
	tmp = malloc(BUFFER_SIZE + 1);
	content[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(read_fd, tmp, BUFFER_SIZE);
		tmp[bytes_read] = '\0';
		append_str(&content, tmp);
	}
	free(tmp);
	return (content);
}

void	append_str(char **str1, char *str2)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	new = malloc(strlen(*str1) + strlen(str2) + 1);
	while ((*str1)[++i])
		new[i] = (*str1)[i];
	while (str2[++j])
		new[i + j] = str2[j];
	new[i + j] = '\0';
	free(*str1);
	*str1 = new;
}
