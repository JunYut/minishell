/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/16 13:59:33 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "gbc.h"

t_node	*parse(t_minishell *vars)
{
	t_node	*ast;

	vars->curr_token = vars->token_list;
	ast = get_expression(vars, 0);
	if (vars->curr_token != NULL && vars->parse_err.type == E_NONE)
		return (set_parse_err_type(vars, E_SYNTAX), ast);
	return (ast);
}

t_node	*get_term(t_minishell *vars)
{
	t_node	*node;
	t_node	*subshell_node;

	if (vars->parse_err.type != E_NONE)
		return (NULL);
	if (is_logic_op_or_pipe(vars->curr_token)
		|| vars->curr_token->type == T_R_BRACKET)
		return (set_parse_err_type(vars, E_SYNTAX), NULL);
	if (vars->curr_token->type == T_L_BRACKET)
	{
		vars->curr_token = vars->curr_token->next;
		node = get_expression(vars, 0);
		if (node == NULL)
			return (NULL);
		if (vars->curr_token == NULL || vars->curr_token->type != T_R_BRACKET)
			return (set_parse_err_type(vars, E_SYNTAX), node);
		subshell_node = init_new_node(N_SUBSHELL);
		if (subshell_node == NULL)
			return (set_parse_err_type(vars, E_MEM), NULL);
		get_subsh_node(vars, node, subshell_node);
		return (subshell_node);
	}
	return (get_simple_cmd(vars));
}

t_node	*get_simple_cmd(t_minishell *vars)
{
	t_node	*node;

	if (vars->parse_err.type != E_NONE)
		return (NULL);
	node = init_new_node(N_CMD);
	if (node == NULL)
		return (set_parse_err_type(vars, E_MEM), NULL);
	while (vars->curr_token != NULL && (vars->curr_token->type == T_WORD
			|| is_redirection(vars->curr_token->type)))
	{
		if (vars->curr_token->type == T_WORD)
		{
			if (join_args(vars, &(node->args)) == false)
				break ;
		}
		else if (is_redirection(vars->curr_token->type))
		{
			if (get_io_list(vars, &(node->io_list)) == false)
				break ;
		}
	}
	return (node);
}

bool	get_io_list(t_minishell *vars, t_io_node **io_list)
{
	t_token_type	redir_type;
	t_io_node		*temp_io;

	if (vars->parse_err.type != E_NONE)
		return (false);
	while (vars->curr_token && is_redirection(vars->curr_token->type))
	{
		redir_type = vars->curr_token->type;
		vars->curr_token = vars->curr_token->next;
		if (vars->curr_token == NULL || vars->curr_token->type != T_WORD)
			return (set_parse_err_type(vars, E_SYNTAX), false);
		temp_io = init_new_io_node(redir_type, vars->curr_token->value);
		if (temp_io == NULL)
			return (set_parse_err_type(vars, E_MEM), false);
		append_io_node(io_list, temp_io);
		vars->curr_token = vars->curr_token->next;
	}
	return (true);
}

t_node	*get_expression(t_minishell *vars, int min_prec)
{
	t_node			*left;
	t_node			*right;
	t_token_type	operator_type;

	if (vars->parse_err.type != E_NONE || vars->curr_token == NULL)
		return (NULL);
	left = get_term(vars);
	if (left == NULL)
		return (NULL);
	while (is_logic_op_or_pipe(vars->curr_token)
		&& token_precedence(vars->curr_token->type) >= min_prec)
	{
		operator_type = vars->curr_token->type;
		vars->curr_token = vars->curr_token->next;
		if (vars->curr_token == NULL)
			return (set_parse_err_type(vars, E_SYNTAX), left);
		right = get_expression(vars, token_precedence(operator_type) + 1);
		if (right == NULL)
			return (left);
		left = build_operator_node(vars, operator_type, left, right);
		if (left == NULL)
			return (clear_ast(&vars->token_list, &left),
				clear_ast(&vars->token_list, &right), NULL);
	}
	return (left);
}
