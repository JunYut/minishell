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

typedef struct s_dirent
{
	t_list	*files;
	t_list	*dot_files;
}	t_dirent;

typedef struct s_wildcard
{
	t_dirent	*dirent;
	t_token		*token;
	char		**pattern;
}	t_wildcard;

char		**wildcard(char *regex, t_env *env);
t_list		*ent_match(t_wildcard *wc, char *regex);
char		*pattern_match(char *ent, t_token *token, char **pattern);
t_token		*tokenize(char *regex);
t_dirent	*init_dirent(char *cwd);
int			count_token(char *regex);
void		sort_lex(t_list *lst);
void		lstswap(t_list *a, t_list *b);
char		**lst_to_arr(t_list *lst);
