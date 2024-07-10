# include "pipe.h"

# ifndef DEBUG
	# define DEBUG 1
# endif
# define PIPE_COUNT 2

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;
	(void)envp;

	# if PIPE_COUNT == 1
	char *cmds[] =
	{
		"/bin/cat",
		"/usr/bin/grep",
		NULL
	};
	char **args[] =
	{
		(char *[]){"cat", "main.c", NULL},
		(char *[]){"grep", "#", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 2
	char *cmds[] =
	{
		"/bin/ls",
		"/usr/bin/grep",
		"/usr/bin/wc",
		NULL
	};
	char **args[] =
	{
		(char *[]){"ls", "-l", NULL},
		(char *[]){"grep", "c", NULL},
		(char *[]){"wc", "-l", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 3
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
	# endif
	# if PIPE_COUNT == 6
	char *cmds[] =
	{
		"/bin/cat",
		"/usr/bin/tr",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		"/usr/bin/sort",
		"/usr/bin/head",
		NULL
	};
	char **args[] =
	{
		(char *[]){"cat", "main.c", NULL},
		(char *[]){"tr", "\'[:upper:]\'", "\'[:lower:]\'", NULL},
		(char *[]){"tr", "-c", "\'[:alnum:]\'", "\'\\n\'", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", "-c", NULL},
		(char *[]){"sort", "-nr", NULL},
		(char *[]){"head", "-10", NULL},
		NULL
	};
	# endif

	int fd[PIPE_COUNT][2] = {0};

	for (int i = 0; i < PIPE_COUNT; i++)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}

	# if DEBUG == 1
	printf("PID: %d\n", getpid());
	printf("PIPE_COUNT: %d\n", PIPE_COUNT);
	printf("\n");
	# endif

	pipex(cmds, args, fd, PIPE_COUNT + 1);

	# if DEBUG == 0
	while (1);
	# endif
}
