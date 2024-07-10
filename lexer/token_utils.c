/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:53:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/10 12:56:52 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_new_token(t_token_type type, char *value)
{
	t_token *token;

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
		return	;
	}
	current = *token_list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = token;
	token->prev = current;
}
