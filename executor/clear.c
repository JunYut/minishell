/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/23 14:41:05 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear(t_minishell *vars)
{
	rl_clear_history();
	clear_ast(&vars->token_list, &vars->ast);
	clear_env(&vars->env);
	free(vars);
	return (0);
}
