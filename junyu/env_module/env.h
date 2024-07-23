# pragma once

# include "gbc.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

# define DEBUG 1
# if DEBUG
	# define DPRINTF printf
# else
	# define DPRINTF(...) do {} while (0)
# endif
# define EXPORT 1
# define VAR 2

typedef struct s_var
{
	int				id;
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_env
{
	t_var	*var;
	t_var	*exp;
}	t_env;

void	env(t_env *e, char lst);
void	export(char *str, t_env *e);
void	unset(char *key, t_env *e);
void	cd(char *path, t_env *e);

void	add_var(t_env *e, char *key, char *val);
void	set_val(t_env *e, char *key, char *val);
char	*fetch_val(char *key, t_env *e);
t_env	*dup_env(char **envp);
void	sort_export(t_var *exp);

char	*parent_dir(char *pwd);

char	**split_var(char *str);
char	*ft_strdup(char *str, int pos);
void	ft_strncpy(char *dst, char *src, int len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str, char delim);
