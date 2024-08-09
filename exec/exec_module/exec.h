# pragma once

# include "pipe.h"
# include "redir.h"
# include "env.h"
# include "libft.h"

typedef enum e_token
{
	T_CMD,
	T_REDIN,
	T_REDOUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_OR,
	T_AND,
	T_END,
	T_INVALID = -1
}	t_token;

// for regular command, set field type to T_CMD
// for && command, set field type to T_AND
// for || command, set field type to T_OR
// field cmd should be the full path of the command
// field argv should be NULL terminated
typedef struct s_cmd
{
	t_token	type;
	char	*cmd;
	char	**argv;
}	t_cmd;

// for T_HERE_DOC and T_PIPE, set field file to NULL
typedef struct s_redir
{
	t_token		type;
	char		*file;
}	t_redir;

// both fields should be terminated by type: T_END
typedef struct s_cmd_line
{
	t_redir	*redirs;
	t_cmd	*cmds;
}	t_cmd_line;

int	cmd_exec(t_cmd_line *cmd, t_env *env);
int	redirect(t_redir *redirs);
int	execute(t_cmd *cmds, t_env *env);
int	exit_status(pid_t pid, t_env *env);
