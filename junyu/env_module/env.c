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

void	env(t_env *e)
{
	t_env	*curr;

	curr = e;
	while (curr->next)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	unset(char *key, t_env *e);

void	export(char *str, t_env *e, t_gbc *gbc)
{
	static int	index;
	char		**split;
	t_env		*curr;

	curr = e;
	while (curr->next)
		curr = curr->next;
	split = split_env(str, gbc);
	curr->index = index++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(gbc, sizeof(t_env));
	curr->next->next = NULL;
}
