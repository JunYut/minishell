# pragma once

# include "enum.h"
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

# ifndef DEBUG
# 	define DEBUG 1
# endif

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

// This will be linked list's content
typedef struct s_cmd_line
{
	char	**identifiers;
	// syntax: [cmd_token] [args_token] [op_token] ...
	t_token	*tokens;
	t_cmd	*cmds;
}	t_cmd_line;

t_cmd_line	*init_cmd(const char *raw, char *envp[]);
t_token		*tokenize(char **identifiers);

// Debugging functions
void	print_cmd(t_cmd_line *cmd);
void	print_paths(char **path_list);
