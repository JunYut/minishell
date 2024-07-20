# include "env.h"

void	init_env(t_env *e, char **envp)
{
	e->var = init_var(envp);
	e->exp = init_export(envp);
	unset("OLDPWD", e);
}

t_var	*init_var(char **envp)
{
	t_var	*v;

	v = dup_env(envp, VAR);
	return (v);
}

t_var	*dup_env(char **envp, char lst)
{
	t_var	*var;
	int		i;

	var = gb_malloc(sizeof(t_var));
	var->next = NULL;
	i = -1;
	while (envp[++i])
		add_var(envp[i], var, lst);
	return (var);
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

void	add_var(char *str, t_var *v, char lst)
{
	static int	id;
	char		**split;
	t_var		*curr;

	curr = v;
	while (curr->next)
		curr = curr->next;
	split = split_var(str);
	if (lst == VAR && split[1] == NULL)
		return ;
	curr->id = id++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}
