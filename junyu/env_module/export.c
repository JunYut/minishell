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
	char	**split;
	t_var	*pos;

	if (str == NULL)
	{
		env(e->exp, 'x');
		return ;
	}
	split = split_var(str);
	if (split == NULL)
	{
		add_var(str, e->var);
		add_var(str, e->exp);
		return ;
	}
	pos = find_key(split[0], e->exp);
	if (pos)
	{
		replace_val(split[1], pos);
	}
	else
		add_var(str, e->exp);
}

t_var	*find_key(char *key, t_var *v)
{
	t_var	*curr;

	curr = v;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	replace_val(char *val, t_var *pos)
{
	t_var	*curr;

	if (pos == NULL)
		return ;
	curr = pos;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, pos->key) == 0)
		{
			curr->value = val;
			return ;
		}
		curr = curr->next;
	}
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
