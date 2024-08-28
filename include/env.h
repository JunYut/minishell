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
	char	**envp;
	t_var	*var;
	t_var	*exp;
	int		last_var_id;
	int		last_exp_id;
}	t_env;

void	env(t_env *e, char lst);
void	export(char **ent, t_env *e);
void	unset(char **keys, t_env *e);
void	cd(char **path, t_env *e);
void	pwd(t_env *e);
void	echo(char **av);

void	add_ent(t_env *e, char *key, char *val);
void	set_val(t_env *e, char *key, char *val);
char	*fetch_val(char *key, t_env *e);
void	rm_ent(char *key, t_var *lst, int last_id);
t_env	*dup_env(char *envp[]);
char	**env_to_arr(t_var *var);
void	sort_export(t_var *exp);

int		valid_key(char *key, t_env *e);
int		path_count(char **path, t_env *e);

char	**split_ent(char *str);
char	*ft_strndup(char *str, int pos);
void	ft_strncpy(char *dst, char *src, int len);
int		find_pos(char *str, char delim);
