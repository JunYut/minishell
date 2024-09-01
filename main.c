/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/30 13:53:28 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile sig_atomic_t g_wait;
void	setup_terminal(t_minishell *vars);

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
	ft_bzero(vars, sizeof(t_minishell));
	// vars->token_list = NULL;
	// vars->curr_token = NULL;
	// vars->ast = NULL;
	// vars->parse_err.type = E_NONE;
	// vars->parse_err.str = NULL;
	// vars->token_err = false;
	// vars->line = NULL;
	vars->envp = envp;
	vars->env = dup_env(envp);
	// setup_terminal(vars);
}

void	setup_terminal(t_minishell *vars)
{
	g_wait = 0;
	tcgetattr(STDIN_FILENO, &vars->term);
	vars->term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->term);
	signal(SIGINT, int_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	vars;
	char		*curr_dir;

	init_vars(&vars, envp);
	((void)ac, (void)av, (void)curr_dir);
	while (1)
	{
		setup_terminal(&vars);
		// env(vars.env, 2);
		curr_dir = fetch_val("PWD", vars.env);
		append_str(&curr_dir, "> ");
		vars.line = readline(curr_dir);
		// vars.line = gb_add(readline("minishell> "));
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
		signal(SIGQUIT, int_sigquit);
		tcsetattr(STDIN_FILENO, TCSANOW, &vars.term);
		exec_node(vars.ast, false, &vars);
		clear_ast(&vars.token_list, &vars.ast);
	}
	clear_history();
	gb_clear();
	return (0);
}
