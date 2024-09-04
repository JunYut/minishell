/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 14:55:46 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
volatile sig_atomic_t g_wait;
void	setup_terminal(t_minishell *vars);

char	*get_node_type(int type)
{
	if (type == N_PIPE)
		return ("PIPE");
	else if (type == N_AND)
		return ("AND");
	else if (type == N_OR)
		return ("OR");
	else
		return ("CMD");
}

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		DPRINTF("%s\n", arr[i]);
}

void	print_tree(t_node *node, int depth, char *branch)
{
	if (depth != 0)
		printf("├─");
	for (int i = 1; i < depth; ++i) {
		printf("─");  // Indentation based on depth
	}
	printf("Node(%s): %s | Value: %s\n", branch, get_node_type(node->type), node->args);
}

void	show_tree(t_node *node, int depth, char *branch)
{
	if (node == NULL)
		return ;
	print_tree(node, depth, branch);
	show_tree(node->left, depth + 1, "left");
	show_tree(node->right, depth + 1, "right");
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
	vars->stdin = dup(STDIN_FILENO);
	vars->stdout = dup(STDOUT_FILENO);
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
		set_val(vars.env, "?", (char *)gb_add(ft_itoa(vars.exit_status)));
		// env(vars.env, 2);
		// curr_dir = fetch_val("PWD", vars.env);
		// append_str(&curr_dir, "> ");
		// vars.line = gb_add(readline(curr_dir));
		if (isatty(fileno(stdin)))
			vars.line = gb_add(readline("minishell> "));
		if (vars.line == NULL)
		{
			printf("exit\n");
			break ;
		}
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
		// show_tree(vars.ast, 0, "root");
		if (vars.parse_err.type != E_NONE)
		{
			handle_parse_error(&vars);
			init_heredocs(vars.ast, &vars); //Init redirections/IO
			continue ;
		}
		// init_heredoc(vars.ast, &vars);
		init_heredocs(vars.ast, &vars); //Init redirections/IO
		signal(SIGQUIT, int_sigquit);
		tcsetattr(STDIN_FILENO, TCSANOW, &vars.term);
		vars.exit_status = exec_node(vars.ast, false, &vars);
		// printf("Exit: %d\n", vars.exit_status);
		clear_ast(&vars.token_list, &vars.ast);
	}
	// gb_clear();
	clear_history();
	return (vars.exit_status);
}
