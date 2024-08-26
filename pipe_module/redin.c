# include "redir.h"

void	redin(char *file)
{
	char	*content;
	int 	pipefd[2];

	content = read_file(file);
	if (!content)
		content = "";
	pipe(pipefd);
	write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

// returns NULL on error
char	*read_file(char *file)
{
	int		fd;
	char	*buf;
	char	*tmp;
	int		bytes_read;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (NULL);
	}
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
