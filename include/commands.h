# pragma once

# include <stdlib.h>
# include <stdio.h>

typedef enum e_token_type	t_token_type;

typedef struct s_cmd_args
{
	const char	*cmd;
	const char	**args;
}	t_cmd_args;

// This will be linked list's content
typedef struct s_cmd
{
	// syntax: [cmd_token] [args_token] [op_token] ...
	const char		*raw;
	const char		**tokens;
	t_cmd_args		*cmds;
	t_token_type	*operators;
}	t_cmd;
