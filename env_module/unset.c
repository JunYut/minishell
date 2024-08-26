# include "env.h"

// keys should be NULL terminated
void	unset(char **keys, t_env *e)
{
	t_var	*curr;
	int		last_id;
	int		i;

	if (keys == NULL || keys[0] == NULL)
		return ;
	i = -1;
	while (keys[++i])
	{
		curr = e->var;
		last_id = e->last_var_id;
		while (curr->next && curr->id != last_id)
		{
			if (ft_strcmp(curr->next->key, keys[i]) == 0)
			{
				if (curr->next->id == last_id)
				{
					last_id = curr->id;
					curr->next->next = NULL;
				}
				else
					curr->next = curr->next->next;
				break;
			}
			curr = curr->next;
		}
		curr = e->exp;
		last_id = e->last_exp_id;
		while (curr->next && curr->id != last_id)
		{
			if (ft_strcmp(curr->next->key, keys[i]) == 0)
			{
				if (curr->next->id == last_id)
				{
					last_id = curr->id;
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
