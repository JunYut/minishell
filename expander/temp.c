#include "expand.h"

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

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	// fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
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
		content = gnl_strjoin(content, tmp);
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
	new = gb_malloc(ft_strlen(*str1) + ft_strlen(str2) + 1);
	while ((*str1)[++i])
		new[i] = (*str1)[i];
	while (str2[++j])
		new[i + j] = str2[j];
	new[i + j] = '\0';
	// free(*str1);
	*str1 = new;
}

char	*parse_path(char *envp[], char *cmd)
{
	char	**path_list;
	char	*path;
	int		i;

	i = -1;
	while (envp[++i] && ft_strncmp(envp[i], "PATH=", 5))
		;
	path_list = ft_split(envp[i], ':');
	prepend_cmd(path_list, cmd);
	trim_path(path_list[0], "PATH=");
	path = NULL;
	i = -1;
	while (path_list[++i] && !path)
		if (access(path_list[i], X_OK) == 0)	// not considering directories
			path = ft_strdup(path_list[i]);
	ft_free_s_arr(path_list);
	return (path);
}

void	trim_path(char *cmd, char *path)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	ft_memmove(cmd, cmd + path_len, ft_strlen(cmd) - path_len);
	cmd[ft_strlen(cmd) - path_len] = '\0';
}

void	prepend_cmd(char **path_list, char *cmd)
{
	int	i;

	i = -1;
	while (path_list[++i])
	{
		path_list[i] = gnl_strjoin(path_list[i], "/");
		path_list[i] = gnl_strjoin(path_list[i], cmd);
	}
}
