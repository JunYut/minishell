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
	static int	id;
	char		**split;
	t_var		*curr;

	curr = e->var;
	while (curr->next)
		curr = curr->next;
	split = split_env(str);
	curr->id = id++;
	curr->key = split[0];
	curr->value = split[1];
	curr->next = gb_malloc(sizeof(t_var));
	curr->next->next = NULL;
}

t_var	*init_export(char **envp)
{
	t_var	*export;

	export = dup_env(envp);
	return (export);
}

// void	sort_export(t_var *exp)
// {

// }
