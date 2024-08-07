# pragma once

# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "define.h"
# include "gbc.h"

void	heredoc(char *delimiter, char *cmd, char *argv[]);
void	redout(int fd, char *cmd, char *argv[]);
void	redin(int fd, char *cmd, char *argv[]);

char	*read_pipe(int read_fd);
char	*read_doc(char *delimiter);
char	*read_file(int fd);
void	append_str(char **str1, char *str2);
