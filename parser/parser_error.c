/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:06:34 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/11 12:00:29 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_parse_err_type(t_minishell *vars, t_parse_err_type type)
{
	vars->parse_err.type = type;
}

void	handle_parse_error(t_minishell *vars)
{
	t_parse_err_type	err_type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_WORD", "<", ">", "<<", ">>", "|", "(", ")", "||",
		"&&", "newline"};
	err_type = vars->parse_err.type;
	if (err_type == E_NONE)
		return ;
	if (err_type == E_SYNTAX)
	{
		if (vars->curr_token == NULL)
			token_type = T_NEWLINE;
		else
			token_type = vars->curr_token->type;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(types[token_type], 2);
		ft_putstr_fd("'\n", 2);
		vars->exit_status = 2;
	}
}
