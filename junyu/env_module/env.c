# include "env.h"

t_var	*dup_env(char **envp)
{
	t_var	*v;
	int		i;

	v = gb_malloc(sizeof(t_var));
	v->next = NULL;
	i = -1;
	while (envp[++i])
	{
		add_var(envp[i], v);
	}
	return (v);
}

void	env(t_var *v)
{
	t_var	*curr;

	curr = v;
	while (curr->next)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	unset(char *key, t_var *v)
{
	t_var	*curr;

	if (key == NULL)
		return ;
	curr = v;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
}

void	add_var(char *str, t_var *v)
{
	static int	id;
	char		**split;
	t_var		*curr;

	curr = v;
	while (curr->next)
		curr = curr->next;
	split = split_env(str);
	curr->id = id++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}
