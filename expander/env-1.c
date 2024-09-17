/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:57:09 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/17 15:48:52 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "utils.h"

void	clear_env(t_env **e)
{
	ft_free_s_arr((*e)->envp);
	(*e)->envp = NULL;
	clear_ent(&(*e)->exp);
	printf("\n");
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

void	new_ent(t_var **lst, char *key, char *val)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	new->key = ft_strdup(key);
	new->value = ft_strdup(val);
	new->next = NULL;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;

}
