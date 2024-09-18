/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:24 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/18 16:34:33 by kkhai-ki         ###   ########.fr       */
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
	// print_arr(e->envp);
	// if (e->envp != NULL)
	// ft_free_s_arr(e->envp);
	e->envp = env_to_arr(e->var);
	return (0);
}

void	rm_ent(char *key, t_var *lst, int last_id)
{
	while (lst)
	{
		// printf("lst->key: [%s]\n", lst->key);
		if (ft_strcmp(lst->key, key) == 0)
		{
			ft_free((void **)&lst->key);
			ft_free((void **)&lst->value);
			if (last_id == 0)
				lst = lst->next;
			else
				lst->next = lst->next->next;
			return ;
		}
		lst = lst->next;
	}
}
