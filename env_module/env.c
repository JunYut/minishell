# include "env.h"

t_env	*dup_env(char *envp[])
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
		split = split_ent(envp[i]);
		add_ent(e, split[0], split[1]);
	}
	unset((char *[]){"OLDPWD", NULL}, e);
	add_ent(e, "?", "0");
	set_val(e, "SHLVL", "1");
	e->envp = env_to_arr(e->var);
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

// a=1 : export: a="1"; var: a=1
// a= : export: a=""; var: a=
// a : export: a; var: [nothing]
// will create an empty entry after key and val is set
void	add_ent(t_env *e, char *key, char *val)
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

int	valid_key(char *key, t_env *e)
{
	int	i;

	if (!key || ft_strchr("1234567890", key[0]) != NULL)
	{
		printf("minishell: export: `%s`: not a valid identifier\n", key);
		set_val(e, "?", "1");
		return (0);
	}
	i = -1;
	while (key[++i])
	{
		if (ft_strchr("!@#$%^&()_+{}|:\"<>?`~-=[]\\;',./", key[i]) != NULL)
		{
			printf("minishell: export: `%s`: not a valid identifier\n", key);
			set_val(e, "?", "1");
			return (0);
		}
	}
	return (1);
}

void	exit_shell(char **status, t_env *e)
{
	int	exit_status;

	printf("exit\n");
	if (count_args(status, "exit", e) > 1)
		exit_status = 1;
	if (status && status[0])
	{
		if (is_numeric(status[0]))
			exit_status = ft_atoi(status[0]);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", status[0]);
			exit_status = 2;
		}
	}
	if (!status || !status[0] || status[0][0] == '\0')
		exit_status = ft_atoi(fetch_val("?", e));
	gb_clear();
	exit(exit_status);
}
