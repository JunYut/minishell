# pragma once

# include "tokenizer.h"
# include <get_next_line.h>
# include <libft.h>

typedef struct s_cmd	t_cmd;

t_cmd	*parse(t_token *tokens, char **identifiers, char *envp[]);
char	*parse_path(char *envp[], char *cmd);
char	*find_bin(char **path_list);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);
