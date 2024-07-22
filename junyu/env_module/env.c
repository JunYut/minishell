# include "env.h"

t_env	*dup_env(char **envp)
{
	t_env	*e;
	char	**split;
	int		i;

	e = gb_malloc(sizeof(t_env));
	e->exp = gb_malloc(sizeof(t_var));
	e->var = gb_malloc(sizeof(t_var));
	e->exp->next = NULL;
	e->var->next = NULL;
	i = -1;
	while (envp[++i])
	{
		split = split_var(envp[i]);
		add_var(e, split[0], split[1]);
	}
	unset("OLDPWD", e);
	return (e);
}

void	env(t_env *e, char lst)
{
	t_var	*curr;

	if (lst == VAR)
		curr = e->var;
	else
		curr = e->exp;
	while (curr->next)
	{
		if (lst == EXPORT)
			printf("declare -x ");
		printf("%s=", curr->key);
		if (lst == EXPORT && curr->value)
			printf("\"%s\"\n", curr->value);
		else if (lst == VAR && curr->value)
			printf("%s\n", curr->value);
		else
			;
		curr = curr->next;
	}
}

void	unset(char *key, t_env *v)
{
	t_var	*curr;

	if (key == NULL)
		return ;
	curr = v->var;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
	curr = v->exp;
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

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	add_var(t_env *e, char *key, char *val)
{
	static int	id;
	t_var		*curr;

	curr = e->exp;
	while (curr->next)
		curr = curr->next;
	curr->id = id++;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
	if (val == NULL)
		return ;
	curr = e->var;
	while (curr->next)
		curr = curr->next;
	curr->id = id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}
