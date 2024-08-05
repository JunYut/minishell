# include "redin.h"

void	redin(char *file, char *cmd, char *argv[])
{
	char	*content;
	pid_t	pid;
	int 	pipefd[2];

	content = read_file(file);
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
	free(content);
}

// returns NULL on error
char	*read_file(char *file)
{
	int		fd;
	char	*buf;
	char	*tmp;
	int		bytes_read;

	fd = open(file, O_RDONLY);
	buf = malloc(1);
	tmp = malloc(READ_SIZE + 1);
	buf[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, READ_SIZE);
		tmp[bytes_read] = '\0';
		append_str(&buf, tmp);
	}
	close(fd);
	free(tmp);
	return (buf);
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

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
