# include "pipe.h"

# ifndef DEBUG
	# define DEBUG 1
# endif
# define PIPE_COUNT 7

int main (void)
{
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
	# if PIPE_COUNT == 4
	char *cmds[] =
	{
		"/bin/echo",
		"/usr/bin/tr",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		NULL
	};
	char **args[] =
	{
		(char *[]){"echo", "Hello, World!", NULL},
		(char *[]){"tr", " ", "-", NULL},
		(char *[]){"tr", "e", "E", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 5
	char *cmds[] =
	{
		"/bin/echo",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		"/usr/bin/tr",
		"/usr/bin/awk",
		NULL
	};
	char **args[] =
	{
		(char *[]){"echo", "Sample text for pipe demonstration", NULL},
		(char *[]){"tr", "\' \'", "\'\\n\'", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", NULL},
		(char *[]){"tr", "\'a-z\'", "\'A-Z\'", NULL},
		(char *[]){"awk", "{print $0 \"-PIPE\"}", NULL},
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
	# if PIPE_COUNT == 7
	char *cmds[] =
	{
		"/bin/sleep",
		"/bin/sleep",
		"/bin/sleep",
		"/bin/echo",
		NULL
	};
	char **args[] =
	{
		(char *[]){"sleep", "2", NULL},
		(char *[]){"sleep", "5", NULL},
		(char *[]){"sleep", "2", NULL},
		(char *[]){"echo", "Hello", NULL},
		NULL
	};
	# endif

	int cmds_count = sizeof(cmds) / sizeof(cmds[0]) - 1;
	int pipe_count = cmds_count - 1;
	int fd[pipe_count][2];

	for (int i = 0; i < pipe_count; i++)
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

	print_pipe(args);

	pipex(cmds, args, fd, pipe_count + 1);

	# if DEBUG == 0
	while (1);
	# endif
}