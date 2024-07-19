# pragma once

# include "gbc.h"
# include <unistd.h>
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

void	init_env(t_env *e, char **envp);
void	env(t_env *e, char lst);
void	export(char *str, t_env *e);
void	unset(char *key, t_env *e);
void	cd(char *path, t_env *e);

void	add_var(char *str, t_var *v, char lst);
void	set_val(t_env *e, char *key, char *val);
char	*fetch_val(char *key, t_var *v);
t_var	*init_var(char **envp);
t_var	*init_export(char **envp);
void	sort_export(t_var *exp);
t_var	*dup_env(char **envp, char lst);

char	*parent_dir(char *pwd);

char	**split_var(char *str);
char	*ft_strdup(char *str, int pos);
void	ft_strncpy(char *dst, char *src, int len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str, char delim);
