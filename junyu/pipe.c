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
	(void)envp;

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
			execve("/usr/bin/ls", (char *[]){"ls", NULL, NULL}, NULL);
		}
		else
		{
			close(fd[1]); // close write end
			dup2(fd[0], 0); // stdout -> fd[0]
			char *args[] = {"grep", ".c", NULL};
			execve("/usr/bin/grep", args, envp);
		}
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
}
