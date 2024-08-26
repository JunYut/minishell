# include "redir.h"

void	heredoc(char *delimiter)
{
	char	*doc;
	int		fd[2];

	doc = read_doc(delimiter);
	pipe(fd);
	write(fd[1], doc, ft_strlen(doc));
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

char	*read_doc(char *delimiter)
{
	char	*doc;
	char	*line;

	doc = gb_malloc(1);
	doc[0] = '\0';
	while (1)
	{
		line = gb_add(readline("> "));
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		append_str(&doc, line);
		append_str(&doc, "\n");
	}
	return (doc);
}
