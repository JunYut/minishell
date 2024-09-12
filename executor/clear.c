/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/12 14:39:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear(t_minishell *vars)
{
	rl_clear_history();
	clear_ast(&vars->token_list, &vars->ast);
	gbc_clear();
	return (0);
}
