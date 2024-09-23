/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/23 13:44:42 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_wait;

int	main(int ac, char **av, char **envp)
{
	t_minishell	*vars;
	int			status;

	(void)ac;
	vars = init_vars(av[0], envp);
	while (1)
	{
		init_prompt(vars);
		if (vars->line == NULL)
			break ;
		if (process_line(vars) || vars->token_list == NULL
			|| vars->parse_err.type != E_NONE)
		{
			ft_bzero(&vars->parse_err, sizeof(t_parse_err));
			clear_ast(&vars->token_list, &vars->ast);
			continue ;
		}
		signal(SIGQUIT, int_sigquit);
		tcsetattr(STDIN_FILENO, TCSANOW, &vars->term);
		vars->exit_status = exec_node(vars->ast, false, vars);
		clear_ast(&vars->token_list, &vars->ast);
	}
	status = vars->exit_status;
	clear(vars);
	return (status);
}

int	process_line(t_minishell *vars)
{
	tokenize(vars->line, vars);
	if (vars->token_list == NULL)
		return (1);
	vars->ast = parse(vars);
	if (vars->parse_err.type != E_NONE)
		handle_parse_error(vars);
	if (init_heredocs(vars->ast, vars) == 1)
	{
		vars->exit_status = 1;
		return (1);
	}
	return (0);
}

int	init_prompt(t_minishell *vars)
{
	setup_terminal(vars);
	vars->line = readline("minishell> ");
	if (vars->line == NULL)
		ft_putstr_fd("exit\n", 2);
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

t_minishell	*init_vars(char *name, char **envp)
{
	static t_minishell	*vars;

	if (vars == NULL)
	{
		vars = malloc(sizeof(t_minishell));
		if (vars == NULL)
			exit(1);
		ft_bzero(vars, sizeof(t_minishell));
		vars->name = name;
		vars->env = dup_env(envp, name);
		vars->ms_stdin = dup(STDIN_FILENO);
		vars->ms_stdout = dup(STDOUT_FILENO);
	}
	return (vars);
}
