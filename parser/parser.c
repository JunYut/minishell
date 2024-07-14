/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/14 14:23:51 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse(t_minishell *vars)
{
	t_node	*ast;

	ast = get_expression(&vars, 0); // Looks for an expression and returns it's root node
	if (vars->curr_token != NULL)
		return (set_parse_err_type(E_SYNTAX), ast);
	return (ast);
}

t_node	*get_expression(t_minishell *vars, int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				next_prec;
	t_token_type	*operator_type;

	if (vars->parse_err.type != E_NONE || vars->curr_token == NULL)
		return (NULL);
	left = get_term(vars);
	if (!left)
		return (NULL);
	while (is_logic_op_or_pipe(vars->curr_token) && token_precedence(vars->curr_token->type) >= min_prec)
	{
		operator_type = vars->curr_token->type;
		vars->curr_token = vars->curr_token->next;
		if (vars->curr_token == NULL)
			return (set_parse_err_type(E_SYNTAX), left);
		next_prec = token_precedence(operator_type) + 1;
		right = get_expression(vars, next_prec);
		if (right == NULL)
			return (left);
		left = build_operator_node(vars, operator_type, left, right);
	}
}
