# pragma once

# ifndef DEBUG
# 	define DEBUG 1
# endif

# include <stdbool.h>
# include <stdio.h>

typedef struct s_cmd_line	t_cmd_line;

void	print_cmd(t_cmd_line *cmd);
void	print_arr(char **arr);
void	debug(char *msg);
