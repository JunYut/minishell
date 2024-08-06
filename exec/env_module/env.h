# pragma once

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"
# include "gbc.h"
# include "define.h"

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
void	export(char **vars, t_env *e);
void	unset(char **keys, t_env *e); //TODO: change to take a list of strings
void	cd(char *path, t_env *e);
void	pwd(t_env *e);
void	echo(char **av);

void	add_var(t_env *e, char *key, char *val);
void	set_val(t_env *e, char *key, char *val);
char	*fetch_val(char *key, t_env *e);
t_env	*dup_env(char **envp);
void	sort_export(t_var *exp);

char	**split_var(char *str);
char	*ft_strndup(char *str, int pos);
void	ft_strncpy(char *dst, char *src, int len);
int		find_pos(char *str, char delim);
