/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:09:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:04:20 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	sort_lex(t_list *lst)
{
	t_list	*curr;
	t_list	*tmp;

	curr = lst;
	while (curr)
	{
		tmp = curr->next;
		while (tmp)
		{
			if (ft_strcmp(curr->content, tmp->content) > 0)
				lstswap(curr, tmp);
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}

void	lstswap(t_list *a, t_list *b)
{
	t_list	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}
