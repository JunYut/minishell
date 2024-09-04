/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:24 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 10:25:33 by tjun-yu          ###   ########.fr       */
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
			break ;
		}
		lst = lst->next;
	}
}
