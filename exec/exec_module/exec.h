# pragma once

# include "pipe.h"
# include "redir.h"
# include "env.h"
# include "libft.h"
# include "define.h"

// field `type` should be T_REDIN, T_REDOUT, T_APPEND
typedef struct s_file
{
	t_token	type;
	char	*file;
}	t_file;

// field `cmd` should be the full path of the command
//  field `argv`
typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	t_file	*file;
	int		file_count;
}	t_cmd;

// field `type` should be T_PIPE, T_AND, T_OR
typedef struct s_pipe
{
	t_token	type;
	t_cmd	*cmd;
	pid_t	*pid;
	int		*pipefd[2];
	int		cmd_count;
	int		pipe_count;
}	t_pipe;

typedef struct s_cmd_line
{
	t_pipe	*seq;
	pid_t	*pid;
	int		exit_status;
	int		seq_count;
}	t_cmd_line;

int	exec(t_cmd_line *cmd, t_env *env);
int pipex();
int	exec_cmd(char *path, char *argv[], char *envp[]);
int	pipe_io(t_token type, int pipefd[][2], int pipe_count);
int	file_io(t_file *file, int file_count);
int	open_pipes(int pipefd[][2], int pipe_count);
int	close_pipes(int pipefd[][2], int pipe_count);
int	wait_childs(pid_t *pid, int count, t_env *env);
int	wait_status(pid_t pid, t_env *env);
