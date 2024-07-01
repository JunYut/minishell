# pragma once

# include <commands.h>
# include <unistd.h>

typedef enum e_token_type	t_token;

int	is_cmd(const char *iden);
int	is_operator(t_token t);
