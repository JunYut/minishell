# include "redin.h"

void	redin(char *cmd, char *file, char *argv[])
{
	int fd = open(file, O_RDONLY);
	int pipefd[2];

	pipe(pipefd);
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);

	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
}

