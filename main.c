/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 16:13:41 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_wait;

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		DPRINTF("%s\n", arr[i]);
}

void	init_vars(t_minishell *vars, char **envp)
{
	vars->token_list = NULL;
	vars->curr_token = NULL;
	vars->ast = NULL;
	vars->parse_err.type = E_NONE;
	vars->parse_err.str = NULL;
	vars->token_err = false;
	vars->line = NULL;
	vars->env = dup_env(envp);
	vars->envp = vars->env->envp;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	vars;
	char		*curr_dir;

	((void)ac, (void)av, (void)curr_dir);
	while (1)
	{
		init_vars(&vars, envp);
		// env(vars.env, 2);
		curr_dir = fetch_val("PWD", vars.env);
		append_str(&curr_dir, "> ");
		// vars.line = readline(curr_dir);
		vars.line = gb_add(readline("minishell> "));
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
		expand_tree(vars.ast, 0, "root", &vars);
		exec_node(vars.ast, false, &vars);
		clear_ast(&vars.token_list, &vars.ast);
	}
	clear_history();
	gb_clear();
	return (0);
}
