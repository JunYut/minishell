# include "pipe.h"

# define CMD_COUNT 7
# define PIPE_COUNT CMD_COUNT - 1

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;
	(void)envp;

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
		(char *[]){"sort", NULL, NULL},
		(char *[]){"uniq", "-c", NULL},
		(char *[]){"sort", "-nr", NULL},
		(char *[]){"head", "-10", NULL},
		NULL
	};
	int *fd[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	for (int i = 0; i < PIPE_COUNT; i++)
		pipe(fd[i]);

	for (int i = 0; fd[i]; i++)
		printf("fd[%d]: %d %d\n", i, fd[i][0], fd[i][1]);

	pipex(cmds, args, fd, PIPE_COUNT);
}
