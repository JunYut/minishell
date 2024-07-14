/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:18:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/14 15:21:49 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_node	*init_new_node(t_node_type type)
{

}

t_node *build_operator_node(t_minishell *vars, t_token_type token_type, t_node *left, t_node *right)
{
	t_node		*node;
	t_node_type	*node_type;

	if (vars->parse_err.type != E_NONE)
		return (NULL);
	if (token_type == T_AND)
		node_type = N_AND;
	else if (token_type == T_OR)
		node_type = N_OR;
	else
		node_type = N_PIPE;
	node = init_new_node(node_type)
}
