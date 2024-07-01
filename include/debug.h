# pragma once

# ifndef DEBUG
# 	define DEBUG 1
# endif

# include <stdio.h>

void	print_cmd(t_cmd_line *cmd);
void	print_paths(char **path_list);
void	debug(char *msg);
