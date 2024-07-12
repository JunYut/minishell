# include "heredoc.h"

void	heredoc(char *cmd, char *args[], char *delimiter)
{
	(void)cmd;
	(void)args;
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
