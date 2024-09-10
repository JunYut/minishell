/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/10 14:51:53 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear(t_minishell *vars)
{
	printf("clear\n");
	clear_history();
	clear_ast(&vars->token_list, &vars->ast);
	gbc_clear();
	return (0);
}
