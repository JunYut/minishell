# pragma once

# include "libft.h"

enum e_token
{
	CMD,
	OPTION,
	ARG,
	OPERATOR,
	HERE_DOC
};

typedef struct s_cmd
{
	char	*raw;
	char	**argv;
	int		*type;
}	t_cmd;

typedef struct s_cmd_table
{
	t_list	*cmd;
	int		cmd_count;
}	t_cmd_table;

t_cmd	*new_cmd(const char *line);
int		*tokenize(const char *argv[]);
int		is_operator(const char *line);
void	free_cmd(void *cmd);
