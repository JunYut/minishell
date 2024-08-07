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
	e->last_exp_id = 0;
	e->last_var_id = 0;
	i = -1;
	while (envp[++i])
	{
		split = split_var(envp[i]);
		add_var(e, split[0], split[1]);
	}
	unset((char *[]){"OLDPWD", NULL}, e);
	add_var(e, "?", "1");
	set_val(e, "SHLVL", "1");
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
		printf("%s", curr->key);
		if (lst == EXPORT && curr->value)
			printf("=\"%s\"", curr->value);
		else if (lst == VAR && curr->value)
			printf("=%s", curr->value);
		else
			;
		printf("\n");
		curr = curr->next;
	}
}

// keys should be NULL terminated
void	unset(char **keys, t_env *e)
{
	t_var	*curr;
	int		i;

	if (keys == NULL || keys[0] == NULL)
		return ;
	i = -1;
	while (keys[++i])
	{
		curr = e->var;
		while (curr->next)
		{
			if (ft_strcmp(curr->next->key, keys[i]) == 0)
			{
				if (curr->next->id == e->last_var_id)
				{
					e->last_var_id = curr->id;
					curr->next->next = NULL;
				}
				else
					curr->next = curr->next->next;
				break;
			}
			curr = curr->next;
		}
		curr = e->exp;
		while (curr->next)
		{
			if (ft_strcmp(curr->next->key, keys[i]) == 0)
			{
				if (curr->next->id == e->last_exp_id)
				{
					e->last_exp_id = curr->id;
					curr->next->next = NULL;
				}
				else
					curr->next = curr->next->next;
				break;
			}
			curr = curr->next;
		}
	}
}

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
void	add_var(t_env *e, char *key, char *val)
{
	t_var		*curr;

	curr = e->exp;
	while (curr->next)
		curr = curr->next;
	e->last_exp_id += 1;
	curr->id = e->last_exp_id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
	if (val == NULL)
		return ;
	curr = e->var;
	while (curr->next)
		curr = curr->next;
	e->last_var_id += 1;
	curr->id = e->last_var_id;
	curr->key = key;
	curr->value = val;
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}
