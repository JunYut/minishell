/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/11 14:43:04 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_minishell *vars)
{
	vars->token_list = NULL;
	vars->curr_token = NULL;
	vars->ast = NULL;
	vars->parse_err.type = 0;
	vars->parse_err.str = NULL;
	vars->token_err = false;
	vars->line = NULL;
}

int	main(void)
{
	t_minishell	vars;

	while (1)
	{
		init_vars(&vars);
		vars.line = readline("minishell> ");
		if (vars.line == NULL)
			break ;
		if (*vars.line != '\0')
			add_history(vars.line);
		vars.token_list = tokenize(vars.line);
		if (vars.token_list == NULL)
			continue ;
		while (vars.token_list != NULL)
		{
			printf("value: %s\n", vars.token_list->value);
			printf("type: %d\n", vars.token_list->type);
			printf("-------------------------------------\n");
			vars.token_list = vars.token_list->next;
		}
	}
	return (0);
}
