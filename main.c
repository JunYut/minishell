/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/10 13:22:35 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

int	main(void)
{
	g_minishell.token_list = NULL;
	g_minishell.line = NULL;
	while (1)
	{
		g_minishell.line = readline("minishell> ");
		if (g_minishell.line == NULL)
			break ;
		if (*g_minishell.line != '\0')
			add_history(g_minishell.line);
		tokenize(g_minishell.line);
		if (g_minishell.token_list == NULL)
			continue ;
		while (g_minishell.token_list != NULL)
		{
			printf("value: %s\n", g_minishell.token_list->value);
			printf("type: %d\n", g_minishell.token_list->type);
			printf("-------------------------------------\n");
			g_minishell.token_list = g_minishell.token_list->next;
		}
	}
	return (0);
}
