# include "env.h"

t_env	*dup_env(char **env)
{
	t_env	*e;
	int		i;

	e = gb_malloc(sizeof(t_env));
	e->next = NULL;
	i = -1;
	while (env[++i])
	{
		simple_export(env[i], e);
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

void	unset(char *key, t_env *e)
{
	t_env	*curr;

	if (key == NULL)
		return ;
	curr = e;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key))
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
}

// only adds a new node now
// TODO:
// - create export list
// - display export list in sorted order when no 'str' is NULL
// - replace value if key already exists
// - add to 'env' when '=' is present
// - add to 'export' when no '=' is present
void	simple_export(char *str, t_env *e)
{
	static int	id;
	char		**split;
	t_env		*curr;

	curr = e;
	while (curr->next)
		curr = curr->next;
	split = split_env(str);
	curr->id = id++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(sizeof(t_env));
	curr->next->next = NULL;
}
