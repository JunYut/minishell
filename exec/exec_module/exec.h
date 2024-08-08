# pragma once

# include "pipe.h"
#include "env.h"

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

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
}	t_cmd;

// for T_PIPE, set field file to NULL
typedef struct s_redir
{
	t_token		type;
	char		*file;
}	t_redir;

typedef struct s_logical
{
	t_token		type;
	t_cmd		*cmd;
}	t_logical;

// field redirs should be terminated by type: T_END
// field cmds should be terminated by cmd: NULL
typedef struct s_cmd_line
{
	t_redir	*redirs;
	t_cmd	*cmds;
}	t_cmd_line;

int	cmd_exec(t_cmd_line *cmd, t_env *env);
