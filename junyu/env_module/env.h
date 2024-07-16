# pragma once

# include "gbc.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_env
{
	int				id;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*dup_env(char **env, t_gbc *gbc);
void	env(t_env *e);
void	unset(char *key, t_env *e);
void	export(char *str, t_env *e, t_gbc *gbc);

char	**split_env(char *str, t_gbc *gbc);
void	ft_strncpy(char *dst, char *src, int len);
bool	ft_strcmp(char *s1, char *s2);
bool	is_key(char c);
int		ft_strlen(char *str, char c);
