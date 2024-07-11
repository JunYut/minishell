# include "redin.h"

void	redin(char *cmd, char *file, char *argv[])
{
	(void)cmd;
	(void)file;
	(void)argv;
	int pipefd[2];

	pipe(pipefd);
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);

	close(pipefd[0]);
	close(pipefd[1]);
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
	tmp = malloc(BUFFER_SIZE + 1);
	buf[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		tmp[bytes_read] = '\0';
		append(&buf, tmp);
	}
	close(fd);
	free(tmp);
	return (buf);
}

void	append(char **str1, char *str2)
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
