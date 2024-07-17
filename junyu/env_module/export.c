# include "env.h"

// only adds a new node now
// TODO:
// - create export list
// - display export list in sorted order when no 'str' is NULL
// - replace value if key already exists
// - add to 'env' when '=' is present
// - add to 'export' when no '=' is present
void	export(char *str, t_env *e)
{
	add_var(str, e->exp);
}

t_var	*init_export(char **envp)
{
	t_var	*export;

	export = dup_env(envp);
	sort_export(export);
	return (export);
}

void sort_export(t_var *exp)
{
	t_var	*curr;
	char	*tmp;

	curr = exp;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, curr->next->key) > 0)
		{
			tmp = curr->key;
			curr->key = curr->next->key;
			curr->next->key = tmp;
			tmp = curr->value;
			curr->value = curr->next->value;
			curr->next->value = tmp;
			curr = exp;
		}
		else
			curr = curr->next;
	}
}
