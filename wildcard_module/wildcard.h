# pragma once

# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "env.h"
# include "libft.h"
# include "debug.h"
# include "gbc.h"

# ifndef DPRINTF
	# define DPRINTF(...) printf(__VA_ARGS__)
# endif

typedef struct s_wildcard
{
	t_list	*files;
	t_list	*dot_files;
}	t_wildcard;

char		**wildcard(char *str, t_env *env);
char		**lst_to_arr(t_list *lst);
t_wildcard	*init_wc(char *cwd);
