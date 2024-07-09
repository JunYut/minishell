# pragma once

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

void	pipex(char *cmds[], char ***args, int fd[][2], int pipe_count);
void	redirect(int fd[][2], int i, int pipe_count);
void	close_fds(int fd[][2], int i, int pipc_count);
