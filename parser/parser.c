/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 11:16:14 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "gbc.h"

t_node	*parse(t_minishell *vars)
{
	t_node	*ast;

	vars->curr_token = vars->token_list;
	ast = get_expression(vars, 0); // Looks for an expression and returns it's root node
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
	if (is_logic_op_or_pipe(vars->curr_token) || vars->curr_token->type == T_R_BRACKET)
		return (set_parse_err_type(vars, E_SYNTAX), NULL);
	if (vars->curr_token->type == T_L_BRACKET)
	{
		vars->curr_token = vars->curr_token->next;
		node = get_expression(vars, 0);
		if (node == NULL)
			// return (set_parse_err_type(vars, E_MEM), NULL); Need to revisit this to see how to properly deal with this
			return (NULL);
		if (vars->curr_token == NULL || vars->curr_token->type != T_R_BRACKET)
			return (set_parse_err_type(vars, E_SYNTAX), node);
		subshell_node = init_new_node(N_SUBSHELL);
		if (subshell_node == NULL)
			return (set_parse_err_type(vars, E_MEM), NULL);
		subshell_node->left = node;
		vars->curr_token = vars->curr_token->next;
		return (subshell_node);
	}
	else
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
	while (vars->curr_token != NULL && (vars->curr_token->type == T_WORD || is_redirection(vars->curr_token->type)))
	{
		if (vars->curr_token->type == T_WORD)
		{
			if (join_args(vars, &(node->args)) == false)
				// return (clear_cmd_node(node), set_parse_err_type(vars, E_MEM), NULL);
				return (clear_cmd_node(node), NULL);
		}
		else if (is_redirection(vars->curr_token->type))
		{
			if (get_io_list(vars, &(node->io_list)) == false)
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}

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
		// printf("Token value: %s\n", vars->curr_token->value);
		quote = get_quote_type(vars->curr_token->value);
		if (quote != 0 && is_quote_balance(vars->curr_token->value, quote) == false)
			return (handle_quote_err(quote, vars), false);
		*args = ft_strjoin_delim(*args, vars->curr_token->value, " "); ///Need to review this later
		// *args = gnl_strjoin(*args, vars->curr_token->value);
		if (*args == NULL)
			return (false);
		vars->curr_token = vars->curr_token->next;
	}
	return (true);
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
	int				next_prec;
	t_token_type	operator_type;

	if (vars->parse_err.type != E_NONE || vars->curr_token == NULL)
		return (NULL);
	left = get_term(vars);
	if (left == NULL)
		return (NULL);
	while (is_logic_op_or_pipe(vars->curr_token) && token_precedence(vars->curr_token->type) >= min_prec)
	{
		operator_type = vars->curr_token->type;
		vars->curr_token = vars->curr_token->next;
		if (vars->curr_token == NULL)
			return (set_parse_err_type(vars, E_SYNTAX), left);
		next_prec = token_precedence(operator_type) + 1;
		right = get_expression(vars, next_prec);
		if (right == NULL)
			return (left);
		left = build_operator_node(vars, operator_type, left, right);
		if (left == NULL)
			return (clear_ast(&vars->token_list, &left), clear_ast(&vars->token_list, &right), NULL);
	}
	return (left);
}
