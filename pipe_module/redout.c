# include "redir.h"

void	redout(char *file, t_token type, char *cmd, char *argv[])
{
	pid_t	pid;
	int		*openfds;

	openfds = redout_o(file, type);
	pid = fork();
	if (pid == 0)
	{
		close(openfds[1]);
		execve(cmd, argv, NULL);
		printf("%s: command not found\n", cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	redout_c((int []){openfds[0], openfds[1]}, openfds[2], openfds[3]);
}

// only opens the file and redirect stdout to the file
// returns an array of 3 unclosed file descriptors and the original stdout fd
// openfds[0]: pipefd[0]
// openfds[1]: pipefd[1]
// openfds[2]: file fd
// openfds[3]: original stdout fd
int	*redout_o(char *file, t_token type)
{
	int		*openfds;
	int		fd;

	if (type == T_REDOUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == T_APPEND)
		fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		return (NULL);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return (NULL);
	}
	openfds = gb_malloc(sizeof(int) * 4);
	openfds[3] = dup(STDOUT_FILENO);
	openfds[2] = fd;
	pipe(openfds);
	dup2(openfds[1], STDOUT_FILENO);
	return (openfds);
}

// should be called after command finish execution
void	redout_c(int pipefd[2], int fd, int stdout_fd)
{
	char	*content;

	close(pipefd[1]);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	content = read_pipe(pipefd[0]);
	close(pipefd[0]);
	write(fd, content, ft_strlen(content));
	close(fd);
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
