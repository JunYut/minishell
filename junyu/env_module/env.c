# include "env.h"

t_env	*dup_env(char **env, t_gbc *gbc)
{
	t_env	*e;
	int		i;

	e = gb_malloc(gbc, sizeof(t_env));
	e->next = NULL;
	i = -1;
	while (env[++i])
	{
		export(env[i], e, gbc);
	}
	return (e);
}

void	env(t_env *e);

void	unset(char *key, t_env *e);

void	export(char *str, t_env *e, t_gbc *gbc)
{
	char	**split;
	t_env	*curr;
	int		i;

	curr = e;
	while (curr->next)
		curr = curr->next;
	split = ft_split(str, gbc);
	i = -1;
	while (split[++i])
	{
		e->key = split[0];
		e->value = split[1];
		e->next = gb_malloc(gbc, sizeof(t_env));
		e = e->next;
	}
	e->next = NULL;
}
