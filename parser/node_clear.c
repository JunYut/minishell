/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:38:34 by we                #+#    #+#             */
/*   Updated: 2024/09/23 14:33:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
}

void	recursive_clear_ast(t_node *node)
{
	if (node == NULL)
		return ;
	free(node->args);
	ft_free_s_arr(node->exp_args);
	clear_io_list(&(node->io_list));
	if (node->left != NULL)
		recursive_clear_ast(node->left);
	if (node->right != NULL)
		recursive_clear_ast(node->right);
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
		ft_free_s_arr(curr_node->exp_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*list = NULL;
}
