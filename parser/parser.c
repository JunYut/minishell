/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/03 13:22:36 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_parse_err_type(t_parse_err_type type)
{
	g_minishell.parse_err.type = type;
}

t_node	*parse(void)
{
	t_node	*ast;

	g_minishell.curr_token = g_minishell.token_list;
	ast = build_ast(0);
}

t_node	*build_ast(int min_prec)
{
	t_node		*left;
	t_node		*right;
	int			n_prec;
	t_token_type	op;

	left = get_term();
	if (!left)
		return (NULL);
	while (is_and_or_pipe(g_minishell.curr_token->type) && token_precedence(g_minishell.curr_token->type) >= min_prec)
	{
		op = g_minishell.curr_token->type;
		g_minishell.curr_token = g_minishell.curr_token->next;
		if (!g_minishell.curr_token)
			return (set_parse_err_type(E_SYNTAX), left);
		n_prec = token_precendence(op + 1);
		right = build_ast(n_prec);
	}
}

t_node	*get_term(void)
{
	t_node	*node;

	if (g_minishell.curr_token->type == T_L_BRACKET)
	{
		g_minishell.curr_token = g_minishell.curr_token->next;
		node = build_ast(0);
		if (!node)
			return (NULL);
		if (!g_minishell.curr_token->type == T_R_BRACKET)
			return (node);
		g_minishell.curr_token = g_minishell.curr_token->next;
		return (node);
	}
	else
		return (get_simple_cmd())
}

t_node	*get_simple_cmd(void)
{
	t_node	*node;

	node = init_new_node(N_CMD);
	if (!node)
		return (set_parse_err_type(E_MEM), NULL);
	while (g_minishell.curr_token->type == T_WORD || is_redirection(g_minishell.curr_token->type))
	{
		if (g_minishell.curr_token->type == T_WORD)
		{
			if (!join_args(&(node->args)))
				return (set_parse_err_type(E_MEM), NULL);
		}
		else if (is_redirection(g_minishell.curr_token->type))
		{
			if (!get_io_list(&(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}

int	join_args(char	**args)
{
	if (!g_minishell.parse_err.type)
		return (FAIL);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (0);
	while (g_minishell.curr_token && g_minishell.curr_token->type == T_WORD)
	{
		*args = ft_strjoin_delim(*args, g_minishell.curr_token->value, " ");
		if (!args)
			return (free(*args), FAIL);
		g_minishell.curr_token = g_minishell.curr_token->next;
	}
	return (SUCCESS);
}

bool	get_io_list(t_io_node **io_list)
{
	t_token_type	redir_type;
	t_io_node		*temp_io;

	if (g_minishell.parse_err.type)
		return (false);
	while (g_minishell.curr_token && is_redirection(g_minishell.curr_token->type))
	{
		redir_type = g_minishell.curr_token->type;
		g_minishell.curr_token = g_minishell.curr_token->next;
		if (!g_minishell.curr_token)
			return (set_parse_err_type(E_SYNTAX), false);
		if (g_minishell.curr_token->type != T_WORD)
			return (set_parse_err_type(E_SYNTAX), false);
		temp_io = init_new_io_node(redir_type, g_minishell.curr_token->value);
		if (!temp_io)
			return (set_parse_err_type(E_MEM), false);
		append_io_node(io_list, temp_io);
		g_minishell.curr_token = g_minishell.curr_token->next;
	}
	return (true);
}

t_node_type	get_node_type(t_token_type type)
{
	if (type == T_AND)
		return (N_AND);
	else if (type == T_OR)
		return (N_OR);
	else if (type == T_PIPE)
		return (N_PIPE);
}

t_io_type	get_io_type(t_token_type type)
{
	if (type == T_REDIRECT_IN)
		return (IO_IN);
	else if (type == T_REDIRECT_OUT)
		return (IO_OUT);
	else if (type == T_HERE_DOC)
		return (IO_HERE_DOC);
	else if (type == T_APPEND)
		return (IO_APPEND);
}

bool	is_and_or_pipe(t_token_type type)
{
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (true);
	return (false);
}

bool	is_redirection(t_token_type type)
{
	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_HERE_DOC || type == T_APPEND)
		return (true);
	return (false);
}

int	token_precedence(t_token_type type)
{
	if (type == T_AND || type == T_OR)
		return (0);
	return (1);
}

t_node	*init_new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_io_node *init_new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = get_io_type(type);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

void ft_append_io_node(t_io_node **list, t_io_node *new_node)
{
	t_io_node	*curr_node;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	curr_node = *list;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_node;
}
