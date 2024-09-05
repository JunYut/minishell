/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:59:22 by we                #+#    #+#             */
/*   Updated: 2024/09/05 17:59:55 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

bool	join_args(t_minishell *vars, char **args)
{
	char	quote;

	if (vars->parse_err.type)
		return (false);
	if (*args == NULL)
		*args = ft_strdup("");
	if (*args == NULL)
		return (false);
	while (vars->curr_token && vars->curr_token->type == T_WORD)
	{
		quote = get_quote_type(vars->curr_token->value);
		if (quote != 0
			&& is_quote_balance(vars->curr_token->value, quote) == false)
			return (handle_quote_err(quote, vars), false);
		*args = ft_strjoin_delim(*args, vars->curr_token->value, " ");
		if (*args == NULL)
			return (false);
		vars->curr_token = vars->curr_token->next;
	}
	return (true);
}
