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

void	env(t_var *v, char lst)
{
	t_var	*curr;

	curr = v;
	while (curr->next)
	{
		if (lst == EXPORT)
			printf("declare -x ");
		printf("%s=", curr->key);
		if (lst == EXPORT && curr->value)
			printf("\"%s\"\n", curr->value);
		else if (lst == VAR)
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

void	add_var(char *str, t_var *v)
{
	static int	id;
	char		**split;
	t_var		*curr;

	curr = v;
	while (curr->next)
		curr = curr->next;
	split = split_var(str);
	curr->id = id++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}
