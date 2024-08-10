# pragma once

# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "define.h"
# include "gbc.h"
# include "debug.h"

void	heredoc(char *delimiter);
void	redin(char *file);
void	redout(char *file, t_token type, char *cmd, char *argv[]);
int		*redout_o(char *file, t_token type);
void	redout_c(int stdout_fd, int fd, int pipefd[2]);

char	*read_pipe(int read_fd);
char	*read_doc(char *delimiter);
char	*read_file(char *file);
void	append_str(char **str1, char *str2);
