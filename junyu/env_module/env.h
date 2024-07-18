# pragma once

# include "gbc.h"
# include <stdbool.h>
# include <stdio.h>

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

t_var	*dup_env(char **envp, char lst);
void	env(t_env *e, char lst);
void	unset(char *key, t_env *e);
void	add_var(char *str, t_var *v, char lst);

void	export(char *str, t_env *e);
void	replace_val(t_env *e, char *key, char *val);
char	*find_key(char *key, t_var *v);
t_var	*init_export(char **envp);
void	sort_export(t_var *exp);

char	**split_var(char *str);
char	*ft_strdup(char *str, char delim);
void	ft_strncpy(char *dst, char *src, int len);
int		ft_strcmp(char *s1, char *s2);
bool	is_delim(char c);
int		ft_strlen(char *str, char delim);
