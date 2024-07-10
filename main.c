/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/10 14:46:55 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

void	init_g_minishell(void)
{
	g_minishell.token_list = NULL;
	g_minishell.curr_token = NULL;
	g_minishell.ast = NULL;
	g_minishell.parse_err.type = 0;
	g_minishell.parse_err.str = NULL;
	g_minishell.token_err = false;
	g_minishell.line = NULL;
}

int	main(void)
{
	while (1)
	{
		init_g_minishell();
		g_minishell.line = readline("minishell> ");
		if (g_minishell.line == NULL)
			break ;
		if (*g_minishell.line != '\0')
			add_history(g_minishell.line);
		tokenize(g_minishell.line);
		if (g_minishell.token_list == NULL)
			continue ;
		// while (g_minishell.token_list != NULL)
		// {
		// 	printf("value: %s\n", g_minishell.token_list->value);
		// 	printf("type: %d\n", g_minishell.token_list->type);
		// 	printf("-------------------------------------\n");
		// 	g_minishell.token_list = g_minishell.token_list->next;
		// }
	}
	return (0);
}
