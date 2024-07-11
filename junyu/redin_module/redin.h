# pragma once

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 1024

void	redin(char *cmd, char *file, char *argv[]);
char	*read_file(char *file);
void	append(char **str1, char *str2);
int		ft_strlen(char *str);
