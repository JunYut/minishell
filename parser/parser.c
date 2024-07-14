/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/14 13:07:00 by kkhai-ki         ###   ########.fr       */
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
}
