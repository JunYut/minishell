# pragma once

# include "gbc.h"
# include <stdbool.h>
# include <stdio.h>

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

t_var	*dup_env(char **envp);
void	env(t_var *e);
void	unset(char *key, t_var *e);
void	add_var(char *str, t_var *e);

void	export(char *str, t_env *e);
t_var	*init_export(char **envp);
void	sort_export(t_var *exp);

char	**split_env(char *str);
void	ft_strncpy(char *dst, char *src, int len);
int		ft_strcmp(char *s1, char *s2);
bool	is_key(char c);
int		ft_strlen(char *str, char c);
