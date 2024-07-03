# pragma once

# include "tokenizer.h"
# include <get_next_line.h>
# include <libft.h>
# include <stdbool.h>

typedef struct s_cmd	t_cmd;

t_cmd	*parse_cmd(t_token *tokens, char **identifiers, char *envp[]);
char	*parse_path(char *envp[], char *cmd);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);
