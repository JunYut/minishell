# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define PROGRAM 1
# define CMD_COUNT 3
# define PIPE_COUNT CMD_COUNT - 1

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;

	// Single pipe
	# if PROGRAM == 0
		int fd[2];
		pid_t pid;

		pipe(fd);	// write: fd[1], read: fd[0]
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]); // close read end
			dup2(fd[1], 1); // stdout -> fd[1]
			execve("/usr/bin/echo", (char *[]){"echo", "Hello world", NULL}, NULL);
		}
		else
		{
			close(fd[1]); // close write end
			dup2(fd[0], 0); // stdout -> fd[0]
			char *args[] = {"cat", NULL, NULL};
			execve("/usr/bin/cat", args, envp);
		}
	# endif

	// Multiple pipe
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
		int fd[PIPE_COUNT][2];
		pid_t pid;

		for (int i = 0; i < PIPE_COUNT; ++i)
			pipe(fd[i]);
		pid = fork();
		if (pid == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				close(fd[0][0]);
				dup2(fd[0][1], STDOUT_FILENO);
				close(fd[0][1]);
				execve(cmds[2], args[2], envp);
			}
			else
			{
				dup2(fd[0][0], STDIN_FILENO);
				close(fd[0][0]);
				dup2(fd[1][1], STDOUT_FILENO);
				close(fd[1][1]);
				execve(cmds[1], args[1], envp);
			}
		}
		else
		{
			close(fd[1][1]);
			dup2(fd[1][0], STDIN_FILENO);
			close(fd[1][0]);
			execve(cmds[0], args[0], envp);
		}
	# endif
}
