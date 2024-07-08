# include "pipe.h"

# define CMD_COUNT 7
# define PIPE_COUNT CMD_COUNT - 1

int main (int ac, char **av, char *envp[])
{
	(void)ac;
	(void)av;

	char *cmds[] =
	{
		"/usr/bin/cat",
		"/usr/bin/tr",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		"/usr/bin/sort",
		"/usr/bin/head"
	};
	char *args[][CMD_COUNT] =
	{
		{"cat", NULL, NULL},
		{"tr", "\'[:upper:]\'", "\'[:lower:]\'", NULL},
		{"tr", "-c", "\'[:alnum:]\'", "\'\\n\'", NULL},
		{"sort", NULL, NULL},
		{"uniq", "-c", NULL},
		{"sort", "-nr", NULL},
		{"head", "-10", NULL}
	};
	int fd[PIPE_COUNT][2];

	for (int i = 0; i < PIPE_COUNT; i++)
		pipe(fd[i]);

	pipex(cmds, args, fd, PIPE_COUNT);
}