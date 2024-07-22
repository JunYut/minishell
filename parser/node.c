/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:18:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/21 16:09:54 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

t_node *build_operator_node(t_minishell *vars, t_token_type token_type, t_node *left, t_node *right)
{
	t_node		*node;
	t_node_type	node_type;

	if (vars->parse_err.type != E_NONE)
		return (NULL);
	if (token_type == T_AND)
		node_type = N_AND;
	else if (token_type == T_OR)
		node_type = N_OR;
	else
		node_type = N_PIPE;
	node = init_new_node(node_type);
	node->left = left;
	node->right = right;
	return (node);
}

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
