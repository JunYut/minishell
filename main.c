/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 17:29:33 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_wait;

int		process_line(t_minishell *vars);
int		init_prompt(t_minishell *vars);
void	setup_terminal(t_minishell *vars);
void	init_vars(t_minishell *vars, char **envp);

int	main(int ac, char **av, char **envp)
{
	t_minishell	vars;
	char		*curr_dir;

	((void)ac, (void)av, (void)curr_dir);
	init_vars(&vars, envp);
	while (1)
	{
		init_prompt(&vars);
		if (vars.line == NULL)
			break ;
		process_line(&vars);
		if (vars.token_list == NULL)
			continue ;
		if (vars.parse_err.type != E_NONE)
			continue ;
		signal(SIGQUIT, int_sigquit);
		tcsetattr(STDIN_FILENO, TCSANOW, &vars.term);
		vars.exit_status = exec_node(vars.ast, false, &vars);
		clear_ast(&vars.token_list, &vars.ast);
	}
	clear_history();
	return (vars.exit_status);
}

int	process_line(t_minishell *vars)
{
	tokenize(vars->line, vars);
	if (vars->token_list == NULL)
		return (0);
	vars->ast = parse(vars);
	if (vars->parse_err.type != E_NONE)
		handle_parse_error(vars);
	return (0);
}

int	init_prompt(t_minishell *vars)
{
	set_val(vars->env, "?", gbc_itoa(vars->exit_status));
	setup_terminal(vars);
	if (isatty(fileno(stdin)))
		vars->line = gbc_add(readline("minishell> "));
	if (vars->line == NULL)
		printf("exit\n");
	if (vars->line == NULL)
		return (0);
	add_history(vars->line);
	return (0);
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

void	init_vars(t_minishell *vars, char **envp)
{
	ft_bzero(vars, sizeof(t_minishell));
	vars->envp = envp;
	vars->env = dup_env(envp);
	vars->stdin = dup(STDIN_FILENO);
	vars->stdout = dup(STDOUT_FILENO);
}
