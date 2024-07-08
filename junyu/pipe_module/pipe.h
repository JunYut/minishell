# pragma once

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define DEBUG 1

void	pipex(char *cmds[], char ***args, int **fd, int pipe_count);
void	redirect(int **fd, int i, int pipe_count);
void	close_fds(int **fd, int i, int pipc_count);
