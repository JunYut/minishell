/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:29:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/10 21:45:01 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **args, int status, t_minishell *vars)
{
	t_env	*env;

	env = vars->env;
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(args + 1, env));
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args + 1));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(env, VAR));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args + 1, env));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd(env));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args + 1, env));
	exit_shell(args + 1, status, vars);
	return (ERRNO_GENERAL);
}

int	exec_child(t_node *node, t_minishell *vars)
{
	t_path	path_status;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		status = check_redir(node);
		if (status != ERRNO_SUCCESS)
			(clear(vars), exit(ERRNO_GENERAL));
		path_status = get_path(node->exp_args[0], vars);
		if (path_status.err.exit_status != ERRNO_SUCCESS)
		{
			status = get_err_msg(path_status.err);
			(clear(vars), exit(status));
		}
		if (ft_strcmp(path_status.cmd_path, vars->name) == 0)
			set_shlvl(vars);
		if (execve(path_status.cmd_path, node->exp_args, vars->env->envp) == -1)
			(clear(vars), exit(ERRNO_GENERAL));
	}
	status = wait_status(pid, vars->env);
	return (status);
}

int	exec_simple_cmd(t_node *node, bool piped, t_minishell *vars)
{
	int	status;

	if (!node->exp_args)
	{
		status = check_redir(node);
		return (ft_reset_stds(piped, vars), (status && ERRNO_GENERAL));
	}
	if (is_builtin(node->exp_args[0]) == true)
	{
		status = check_redir(node);
		if (status != ERRNO_SUCCESS)
			return (ft_reset_stds(piped, vars), ERRNO_GENERAL);
		status = exec_builtin(node->exp_args, vars->exit_status, vars);
		return (ft_reset_stds(piped, vars), status);
	}
	return (exec_child(node, vars));
}

int	exec_node(t_node *node, bool piped, t_minishell *vars)
{
	int	status;

	if (!node)
		return (ERRNO_GENERAL);
	expand_node(node, vars);
	if (node->type == N_PIPE)
		return (exec_pipeline(node, vars));
	if (node->type == N_AND || node->type == N_OR)
	{
		status = exec_node(node->left, false, vars);
		if (node->type == N_AND && status == ERRNO_SUCCESS)
			return (exec_node(node->right, false, vars));
		if (node->type == N_OR && status != ERRNO_SUCCESS)
			return (exec_node(node->right, false, vars));
		return (status);
	}
	if (node->type == N_SUBSHELL)
	{
		status = exec_subshell(node, vars);
		if (status == ERRNO_SUCCESS)
			return (status);
	}
	return (exec_simple_cmd(node, piped, vars));
}

int	exec_subshell(t_node *subshell_node, t_minishell *vars)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		status = exec_node(subshell_node->left, false, vars);
		clear(vars);
		exit(status);
	}
	else if (pid == -1)
		return (ERRNO_GENERAL);
	else
		return (wait_status(pid, vars->env));
	return (ERRNO_GENERAL);
}
