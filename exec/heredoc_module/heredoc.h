# pragma once

# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "define.h"

void	heredoc(char *delimiter, char *cmd, char *args[]);
char	*read_doc(char *delimiter);
void	append_str(char **str1, char *str2);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
