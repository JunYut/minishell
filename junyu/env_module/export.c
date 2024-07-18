# include "env.h"

// if str is NULL, print the export list
// if a key is found in the export list, replace the value, else:
// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	export(char *str, t_env *e)
{
	char	**split;
	char	*key;

	if (str == NULL || str[0] == '\0')
	{
		env(e, EXPORT);
		return ;
	}
	split = split_var(str);
	key = find_key(split[0], e->exp);
	if (split[1] == NULL)
		add_var(str, e->exp, EXPORT);
	else if (key)
		replace_val(e, split[0], split[1]);
	else
	{
		add_var(str, e->exp, EXPORT);
		add_var(str, e->var, VAR);
	}
}

char	*find_key(char *key, t_var *v)
{
	t_var	*curr;

	curr = v;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->key);
		curr = curr->next;
	}
	return (NULL);
}

void	replace_val(t_env *e, char *key, char *val)
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

t_var	*init_export(char **envp)
{
	t_var	*export;

	export = dup_env(envp, EXPORT);
	if (find_key("OLDPWD", export) == NULL)
		add_var("OLDPWD", export, EXPORT);
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
