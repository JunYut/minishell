# pragma once

# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

# ifndef DEBUG
# 	define DEBUG 1
# endif

typedef enum e_token_type
{
	T_IDEN,
	T_CMD,
	T_ARG,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_L_PAREN,
	T_R_PAREN,
	T_SUBSHELL,
	T_OR,
	T_AND,
	T_NEWLINE,
	T_INVALID = -1
}	t_token_type;

typedef struct s_cmd_args
{
	char	*cmd;
	char	**args;
}	t_cmd_args;

// This will be linked list's content
typedef struct s_cmd
{
	char			**identifiers;
	// syntax: [cmd_token] [args_token] [op_token] ...
	t_token_type	*tokens;
	t_cmd_args		*cmds;
	t_token_type	*operators;
}	t_cmd;

t_cmd			*init_cmd(const char *raw);
t_token_type	*tokenize(char **identifiers);

void	print_cmd(t_cmd *cmd);
void	debug(char *msg);
