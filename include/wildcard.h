# pragma once

# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "env.h"
# include "libft.h"
# include "define.h"
# include "gbc.h"
# include "debug.h"

# ifndef DPRINTF
	# define DPRINTF(...) printf(__VA_ARGS__)
# endif

typedef struct s_wildcard
{
	t_list	*files;
	t_list	*dot_files;
	t_token	*token;
	char	**pattern;
}	t_wildcard;

char		**wildcard(char *str, t_env *env);
char		**lst_to_arr(t_list *lst);
t_wildcard	*init_wc(char *cwd);
t_token		*tokenize(char *str);
int			count_token(char *str);
void		sort_lex(t_list *lst);
void		lstswap(t_list *a, t_list *b);
