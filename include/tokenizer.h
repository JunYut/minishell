# pragma once

# include "enum.h"
# include "libft.h"

t_token	*tokenize(char **identifiers, char *envp[]);
t_token	iden_type(char *str, char *envp[]);
