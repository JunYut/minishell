# include "redir.h"

// Append: O_APPEND | O_WRONLY | O_CREAT, 0644
// Redout: O_WRONLY | O_CREAT | O_TRUNC, 0644
// Will close fd
void	redout(int fd, char *cmd, char *argv[])
{
	char	*content;
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(cmd, argv, NULL);
	}
	close(pipefd[1]);
	wait(NULL);
	content = read_pipe(pipefd[0]);
	write(fd, content, ft_strlen(content));
	close(fd);
	close(pipefd[0]);
}

char	*read_pipe(int read_fd)
{
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = gb_malloc(1);
	tmp = gb_malloc(READ_SIZE + 1);
	content[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(read_fd, tmp, READ_SIZE);
		tmp[bytes_read] = '\0';
		append_str(&content, tmp);
	}
	return (content);
}

void	append_str(char **str1, char *str2)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	new = gb_malloc(ft_strlen(*str1) + ft_strlen(str2) + 1);
	while ((*str1)[++i])
		new[i] = (*str1)[i];
	while (str2[++j])
		new[i + j] = str2[j];
	new[i + j] = '\0';
	*str1 = new;
}
