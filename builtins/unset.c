/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:24 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/19 15:03:34 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **keys, t_env *e)
{
	int	i;

	if (keys == NULL || keys[0] == NULL)
		return (ERRNO_SUCCESS);
	i = -1;
	while (keys[++i])
	{
		rm_ent(keys[i], e->exp, e->last_exp_id);
		rm_ent(keys[i], e->var, e->last_var_id);
	}
	ft_free_s_arr(e->envp);
	e->envp = env_to_arr(e->var);
	return (0);
}

void	rm_ent(char *key, t_var *lst, int last_id)
{
	t_var	*curr;

	if (find_ent(key, lst) && find_ent(key, lst)->id == last_id)
	{
		ft_free((void **)&lst->key);
		ft_free((void **)&lst->value);
		ft_free((void **)&lst);
		return ;
	}
	curr = lst;
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			ft_free((void **)&curr->next->key);
			ft_free((void **)&curr->next->value);
			free(curr->next);
			if (curr->next->next)
				curr->next = curr->next->next;
			else
				curr->next = NULL;
			break ;
		}
		curr = curr->next;
	}
}
