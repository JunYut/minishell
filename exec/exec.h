# pragma once

typedef enum e_token
{
	T_CMD,
	T_ARG,
	T_REDIN,
	T_REDOUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_L_PAREN,
	T_R_PAREN,
	T_SUBSH,
	T_OR,
	T_AND,
	T_NEWLINE,
	T_INVALID = -1
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
}	t_cmd;

typedef struct s_redir
{
	t_token		type;
	char		*file;
}	t_redir;

typedef struct s_exec
{
	t_token	*seq;
	t_redir	*redirs;
	t_cmd	*cmds;
}	t_exec;
