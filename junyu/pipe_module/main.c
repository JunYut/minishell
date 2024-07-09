# include "pipe.h"

# ifndef DEBUG
	# define DEBUG 0
# endif
# define CMD_COUNT 7
# define PIPE_COUNT CMD_COUNT - 1

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;
	(void)envp;

	# if PIPE_COUNT == 1
	char *cmds[] =
	{
		"/usr/bin/cat",
		"/usr/bin/head",
		NULL
	};
	char **args[] =
	{
		(char *[]){"cat", "main.c", NULL},
		(char *[]){"head", "-10", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 6
	char *cmds[] =
	{
		"/usr/bin/cat",
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
		pipe(fd[i]);

	# if DEBUG == 1
	printf("PIPE_COUNT: %d\n", PIPE_COUNT);
	for (int i = 0; i < PIPE_COUNT; i++)
	{
		printf("fd[%d][0]: %d\n", i, fd[i][0]);
		printf("fd[%d][1]: %d\n", i, fd[i][1]);
	}
	# endif

	pipex(cmds, args, fd, PIPE_COUNT);
}
