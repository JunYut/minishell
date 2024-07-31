# pragma once

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 1

void	append(char *file, char *cmd, char *args[]);
void	write_file(char *file, char *content);
char	*read_pipe(int read_fd);
void	append_s(char **str1, char *str2);
int		ft_strlen(char *str);
