# include "redout.h"

void	append(char *file, char *cmd, char *args[])
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
		execve(cmd, args, NULL);
	}
	close(pipefd[1]);
	wait(NULL);
	content = read_pipe(pipefd[0]);
	write_file(file, content);
	free(content);
	close(pipefd[0]);
}

void	write_file(char *file, char *content)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, content, ft_strlen(content));
	close(fd);
}

char	*read_pipe(int read_fd)
{
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = malloc(1);
	tmp = malloc(READ_SIZE + 1);
	content[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(read_fd, tmp, READ_SIZE);
		tmp[bytes_read] = '\0';
		append_str(&content, tmp);
	}
	free(tmp);
	return (content);
}

void	append_str(char **str1, char *str2)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	new = malloc(ft_strlen(*str1) + ft_strlen(str2) + 1);
	while ((*str1)[++i])
		new[i] = (*str1)[i];
	while (str2[++j])
		new[i + j] = str2[j];
	new[i + j] = '\0';
	free(*str1);
	*str1 = new;
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
