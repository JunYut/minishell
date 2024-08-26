# include "env.h"

// vars should be NULL terminated
// if str is NULL, print the export list
// if a key is found in the export list, replace the value, else:
// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	export(char **vars, t_env *e)
{
	char	**split;
	char	*value;
	int		i;

	if (vars == NULL || vars[0] == NULL || vars[0][0] == '\0')
	{
		env(vars, e, EXPORT);
		return ;
	}
	i = -1;
	while (vars[++i])
	{
		split = split_ent(vars[i]);
		value = fetch_val(split[0], e);
		if (value)
			set_val(e, split[0], split[1]);
		else
			add_ent(e, split[0], split[1]);
	}
}

// if key is not found, return NULL
char	*fetch_val(char *key, t_env *e)
{
	t_var	*curr;

	curr = e->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	set_val(t_env *e, char *key, char *val)
{
	t_var	*curr;

	curr = e->exp;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			curr->value = val;
			break;
		}
		curr = curr->next;
	}
	curr = e->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			curr->value = val;
			return ;
		}
		curr = curr->next;
	}
}

void sort_export(t_var *exp)
{
	t_var	*curr;
	char	*tmp;

	curr = exp;
	while (curr->next && curr->next->next)
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