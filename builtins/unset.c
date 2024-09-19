/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:24 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/19 23:11:28 by we               ###   ########.fr       */
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
		rm_ent(keys[i], &e->exp);
		rm_ent(keys[i], &e->var);
	}
	ft_free_s_arr(e->envp);
	e->envp = env_to_arr(e->var);
	return (0);
}

void rm_ent(char *key, t_var **lst)
{
	t_var	*curr;
	t_var	*prev;

	curr = *lst;
	prev = NULL;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)
				*lst = curr->next;
			else
				prev->next = curr->next;
			ft_free((void **)&curr->key);
			ft_free((void **)&curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}
