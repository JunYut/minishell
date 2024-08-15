# pragma once

# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "env.h"
# include "libft.h"
# include "gbc.h"

# ifndef DPRINTF
	# define DPRINTF(...) printf(__VA_ARGS__)
# endif

typedef struct s_wildcard
{
	char	*str;
}	t_wildcard;

char	**wildcard(char *str, t_env *env);

void	print_arr(char **arr);
