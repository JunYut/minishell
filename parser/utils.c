/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:02:19 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/17 20:09:32 by kkhai-ki         ###   ########.fr       */
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

int	token_precedence(t_token_type type)
{
	if (type == T_AND || type == T_OR)
		return (0);
	return (1);
}

bool	is_redirection(t_token_type type)
{
	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_HERE_DOC || type == T_APPEND)
		return (true);
	return (false);
}

t_io_type	get_io_type(t_token_type type)
{
	if (type == T_REDIRECT_IN)
		return (IO_IN);
	else if (type == T_REDIRECT_OUT)
		return (IO_OUT);
	else if (type == T_HERE_DOC)
		return (IO_HERE_DOC);
	else
		return (IO_APPEND);
}

char	get_quote_type(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '"')
			return (*str);
		str++;
	}
	return (0);
}
