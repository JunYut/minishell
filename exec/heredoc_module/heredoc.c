# include "heredoc.h"

void	heredoc(char *delimiter, char *cmd, char *args[])
{
	char	*doc;
	pid_t	pid;
	int		fd[2];

	doc = read_doc(delimiter);
	if (cmd)
	{
		pipe(fd);
		write(fd[1], doc, ft_strlen(doc));
		close(fd[1]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			execve(cmd, args, NULL);
		}
		close(fd[0]);
		wait(NULL);
	}
	free(doc);
}

char	*read_doc(char *delimiter)
{
	char	*doc;
	char	*line;

	doc = malloc(1);
	doc[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		append_s(&doc, line);
		append_s(&doc, "\n");
		free(line);
	}
	return (doc);
}

void	append_s(char **str1, char *str2)
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
