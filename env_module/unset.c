# include "env.h"

// keys should be NULL terminated
void	unset(char **keys, t_env *e)
{
	int	i;

	if (keys == NULL || keys[0] == NULL || !valid_key(keys[0]))
		return ;
	i = -1;
	while (keys[++i])
	{
		unset_ent(keys[i], e->exp, e->last_exp_id);
		unset_ent(keys[i], e->var, e->last_var_id);
	}
}

void	unset_ent(char *key, t_var *lst, int last_id)
{
	while (lst->next && lst->id != last_id)
	{
		if (ft_strcmp(lst->next->key, key) == 0)
		{
			if (lst->next->id == last_id)
			{
				last_id = lst->id;
				lst->next->next = NULL;
			}
			else
				lst->next = lst->next->next;
			break;
		}
		lst = lst->next;
	}
}
