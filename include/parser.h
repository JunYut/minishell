# pragma once

# include <get_next_line.h>
# include <libft.h>

char	**parse_path(char *envp[], char *cmd);
char	*trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);
