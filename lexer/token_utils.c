/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:53:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:10:45 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*init_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_to_list(t_token **token_list, t_token *token)
{
	t_token	*current;

	if (*token_list == NULL)
	{
		*token_list = token;
		return ;
	}
	current = *token_list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = token;
	token->prev = current;
}

void	clear_token_list(t_token **list)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *list;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*list = NULL;
}
