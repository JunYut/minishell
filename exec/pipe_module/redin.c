# include "redir.h"

// Open file with O_RDONLY
// Will close fd
void	redin(int fd, char *cmd, char *argv[])
{
	char	*content;
	pid_t	pid;
	int 	pipefd[2];

	content = read_file(fd);
	pipe(pipefd);
	write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		execve(cmd, argv, NULL);
	}
	close(pipefd[0]);
	wait(NULL);
}

// returns NULL on error
char	*read_file(int fd)
{
	char	*buf;
	char	*tmp;
	int		bytes_read;

	buf = gb_malloc(1);
	tmp = gb_malloc(READ_SIZE + 1);
	buf[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, READ_SIZE);
		tmp[bytes_read] = '\0';
		append_str(&buf, tmp);
	}
	close(fd);
	return (buf);
}
