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
	int		fd;
}	t_file;

// field `cmd` should be the full path of the command
//  field `argv` and `file` should be NULL terminated
typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	t_file	*file;
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
	int		exit_status;
}	t_cmd_line;

int	cmd_exec(t_cmd_line *cmd, t_env *env);
int	wait_status(pid_t pid, t_env *env);
