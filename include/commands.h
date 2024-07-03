# pragma once

# include "tokenizer.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <libft.h>

// [cmd] [args] [operator] ...
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		argc;
}	t_cmd;

// [cmd] < [file] [options] or [cmd] > [file] [options]
typedef struct s_redirect
{
	t_token	type;
	char	*file;
	char	**options;
}	t_redirect;

// [cmd] | [cmd]
typedef struct s_pipe
{
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

// This will be linked list's content
typedef struct s_cmd_line
{
	// TODO: execution list
	t_cmd	*cmds;
	t_token	*tokens;
	char	**identifiers;
}	t_cmd_line;

t_cmd_line	*init_cmd(const char *raw, char *envp[]);
