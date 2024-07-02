# pragma once

# ifndef DEBUG
# 	define DEBUG 1
# endif

# include <stdio.h>

typedef struct s_cmd_line	t_cmd_line;

void	print_cmd(t_cmd_line *cmd);
void	print_paths(char **path_list);
void	debug(char *msg);
