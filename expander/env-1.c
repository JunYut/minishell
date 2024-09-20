/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:57:09 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/20 11:24:04 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "utils.h"

void	clear_env(t_env **e)
{
	ft_free_s_arr((*e)->envp);
	clear_ent(&(*e)->exp);
	clear_ent(&(*e)->var);
	ft_free((void **)e);
}

void	clear_ent(t_var ** lst)
{
	t_var	*curr;
	t_var	*next;

	curr = *lst;
	while (curr)
	{
		next = curr->next;
		ft_free((void **)&curr->key);
		ft_free((void **)&curr->value);
		ft_free((void **)&curr);
		curr = next;
	}
	*lst = NULL;
}

void	new_ent(t_var **lst, char *key, char *val, int last_id)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	new->key = ft_strdup(key);
	if (!val)
		new->value = NULL;
	else
		new->value = ft_strdup(val);
	new->next = NULL;
	if (*lst == NULL)
	{
		new->id = 1;
		*lst = new;
		return ;
	}
	new->id = last_id;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}

// if key is not found, return NULL
t_var	*find_ent(char *key, t_var *lst)
{
	t_var	*curr;

	curr = lst;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
