/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/30 22:27:51 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	if ()
}
