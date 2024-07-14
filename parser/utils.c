/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:02:19 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/14 14:10:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_logic_op_or_pipe(t_token *token)
{
	t_token_type	type;

	if (token == NULL)
		return (false);
	type = token->type;
	if (type == T_AND || type == T_OR || type == T_PIPE)
		return (true);
	return (false);
}

int	token_precedence(t_token_type *type)
{
	if (type == T_AND || type == T_OR)
		return (0);
	return (1);
}

void	get_next_token(t_token **list)
{
	*list = (*list)->next;
}
