/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:38:34 by we                #+#    #+#             */
/*   Updated: 2024/09/05 17:40:10 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node->args);
}

void	recursive_clear_ast(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == N_CMD)
		clear_cmd_node(node);
	else
	{
		if (node->left != NULL)
			recursive_clear_ast(node->left);
		if (node->right != NULL)
			recursive_clear_ast(node->right);
	}
	free(node);
}

void	clear_ast(t_token **token_list, t_node **ast)
{
	recursive_clear_ast(*ast);
	*ast = NULL;
	if (token_list != NULL)
		clear_token_list(token_list);
}

void	clear_io_list(t_io_node **list)
{
	t_io_node	*curr_node;
	t_io_node	*next;

	curr_node = *list;
	if (curr_node == NULL)
		return ;
	while (curr_node != NULL)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*list = NULL;
}
