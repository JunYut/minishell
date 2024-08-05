/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/05 12:24:22 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_minishell *vars)
{
	vars->token_list = NULL;
	vars->curr_token = NULL;
	vars->ast = NULL;
	vars->parse_err.type = E_NONE;
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
		// if (*vars.line != '\0')
			add_history(vars.line);
		tokenize(vars.line, &vars);
		if (vars.token_list == NULL)
			continue ;
		// while (vars.token_list != NULL)
		// {
		// 	printf("value: %s\n", vars.token_list->value);
		// 	printf("type: %d\n", vars.token_list->type);
		// 	printf("-------------------------------------\n");
		// 	vars.token_list = vars.token_list->next;
		// }
		vars.ast = parse(&vars);
		if (vars.parse_err.type != E_NONE)
			handle_parse_error(&vars);
		expand_tree(vars.ast);
		free(vars.line);
		clear_ast(&vars.token_list, &vars.ast);
	}
	// gb_clear();
	// clear_history();
	return (0);
}
