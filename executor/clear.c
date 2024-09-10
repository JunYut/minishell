/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/10 15:17:25 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear(t_minishell *vars)
{
	clear_history();
	clear_ast(&vars->token_list, &vars->ast);
	gbc_clear();
	return (0);
}
