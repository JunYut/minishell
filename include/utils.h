# pragma once

# include "tokenizer.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

int		is_cmd(const char *iden);
int		is_operator(t_token t);
void	free_2d(void **arr);
