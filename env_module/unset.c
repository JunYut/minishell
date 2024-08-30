# include "env.h"

// keys should be NULL terminated
int	unset(char **keys, t_env *e)
{
	int	i;

	if (keys == NULL || keys[0] == NULL)
		return ;
	i = -1;
	while (keys[++i])
	{
		if (!valid_key(keys[i], e))
			continue ;
		rm_ent(keys[i], e->exp, e->last_exp_id);
		rm_ent(keys[i], e->var, e->last_var_id);
	}
	e->envp = env_to_arr(e->var);
	return (0);
}

void	rm_ent(char *key, t_var *lst, int last_id)
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
