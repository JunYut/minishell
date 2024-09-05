/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:18:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 17:39:19 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_node	*init_new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_io_node	*init_new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_io_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = get_io_type(type);
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
		return (free(new_node), NULL);
	return (new_node);
}

t_node	*build_operator_node(t_minishell *vars, t_token_type type,
	t_node *left, t_node *right)
{
	t_node		*node;
	t_node_type	node_type;

	if (vars->parse_err.type != E_NONE)
		return (NULL);
	if (type == T_AND)
		node_type = N_AND;
	else if (type == T_OR)
		node_type = N_OR;
	else
		node_type = N_PIPE;
	node = init_new_node(node_type);
	node->left = left;
	node->right = right;
	return (node);
}

void	append_io_node(t_io_node **list, t_io_node *new_node)
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
