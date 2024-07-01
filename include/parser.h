# pragma once

# include <get_next_line.h>
# include <libft.h>

char	**path_parser(char *envp[], char *cmd);
char	*trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);
