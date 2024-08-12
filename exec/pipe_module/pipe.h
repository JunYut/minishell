# pragma once

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

void	pipex(char *cmds[], char ***argv, int fd[][2], int cmd_count);
int		*pipe_o(void);
int		pipe_c(int pipefd[2], int stdio_fd[2]);
void	redir_io(int fd[][2], int i, int pipe_count);
void	close_fds(int fd[][2], int pipe_count);
void	print_pipe(char **argv[]);
