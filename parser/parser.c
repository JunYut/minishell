/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/01 13:26:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// t_node	*parse(void)
// {
// 	t_node	*ast;

// 	g_minishell.curr_token = g_minishell.token_list;
// 	ast = build_ast(0);
// }

// t_node	*build_ast(int min_prec)
// {
// 	t_node		*left;
// 	t_node		*right;
// 	int			n_prec;
// 	t_token_type	op;

// 	left = get_term();
// }

// t_node	*get_term(void)
// {
// 	t_node	*node;

// 	if (g_minishell.curr_token->type == T_L_BRACKET)
// 	{
// 		g_minishell.curr_token = g_minishell.curr_token->next;
// 		node = build_ast(0);
// 		if (!node)
// 			return (NULL);
// 		if (!g_minishell.curr_token->type == T_R_BRACKET)
// 			return (node);
// 		g_minishell.curr_token = g_minishell.curr_token->next;
// 		return (node);
// 	}
// 	else
// 		return (get_simple_cmd())
// }

// t_node	*get_simple_cmd(void)
// {
// 	t_node	*node;

// 	node = init_new_node(N_CMD);
// 	while (g_minishell.curr_token->type == T_WORD || is_redirection(g_minishell.curr_token->type))
// 	{
// 		if (g_minishell.curr_token->type == T_WORD)
// 		{
// 			if (!)
// 		}
// 	}
// }

// int	join_args(char	**args)
// {
// 	char	*to_free;

// 	if (!g_minishell.parse_err.type)
// 		return (FAIL);
// 	if (!*args)
// 		*args = ft_strdup("");
// 	if (!*args)
// 		return (0);
// 	while ()
// }

// bool	is_redirection(t_token_type type)
// {
// 	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_HERE_DOC || type == T_APPEND)
// 		return (true);
// 	return (false);
// }

// t_node	*init_new_node(t_node_type type)
// {
// 	t_node	*new_node;

// 	new_node = ft_calloc(1, sizeof(t_node));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->type = type;
// 	return (new_node);
// }
