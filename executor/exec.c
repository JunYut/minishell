/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:29:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 19:33:21 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_stds(bool piped, t_minishell *vars)
{
	if (piped)
		return ;
	dup2(vars->stdin, 0);
	dup2(vars->stdout, 1);
}

int	get_err_msg(t_err err)
{
	if (err.msg == ERR_MSG_CMD_NOT_FOUND)
	{
		ft_putstr_fd(err.cause, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (err.msg == ERR_MSG_AMBIGUOUS)
	{
		ft_putstr_fd("minishell: *: ambiguous redirect\n", 2);
	}
	else if (err.msg == ERR_MSG_PERM_DENIED)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(err.cause, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (err.exit_status);
	}
	// return (err.exit_status);
	else if (errno == 21)
	{
		// printf("%d\n", errno);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(err.cause, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (ERRNO_CANT_EXEC);
	}
	else if (errno == 2)
	{
		// printf("%d\n", errno);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(err.cause, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (ERRNO_NOT_FOUND);
	}
	return (err.exit_status);
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

t_err	check_exec(char *file)
{
	int	fd;
	(void)fd;

	if (!*file)
		return ((t_err){ERRNO_GENERAL, ERR_MSG_NO_SUCH_FILE, file});
	fd = open(file, O_WRONLY);
	// printf("%d\n", errno);
	if (errno == 21 || errno == 2)
			return ((t_err){ERRNO_CANT_EXEC, ERR_MSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ERRNO_CANT_EXEC, ERR_MSG_PERM_DENIED, file});
		return ((t_err){ERRNO_SUCCESS, -1, NULL});
	}
	return ((t_err){ERRNO_NOT_FOUND, ERR_MSG_CMD_NOT_FOUND, file});
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

int	exec_builtin(char **args, t_env *env)
{
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
	exit_shell(args + 1, env);
	return (ERRNO_GENERAL);
}


t_path	get_path(char *cmd, t_minishell *vars)
{
	char	*full_cmd;

	// printf("Did it reach get_path?\n");
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){check_exec(cmd), cmd});
	full_cmd = parse_path(vars->envp, cmd);
	// DPRINTF("full_cmd: %s\n", full_cmd);
	if (full_cmd != NULL)
		return ((t_path){(t_err){ERRNO_SUCCESS, -1, NULL}, full_cmd});
	return ((t_path){(t_err){ERRNO_NOT_FOUND, ERR_MSG_CMD_NOT_FOUND, cmd}, NULL});
}

int	exec_child(t_node *node, t_minishell *vars)
{
	t_path	path_status;
	int		status;
	pid_t	pid;

	// if (is_builtin(node->exp_args[0]) == true)
	// 		return (exec_builtin(node->exp_args, vars->env));
	pid = fork();
	if (pid == 0)
	{
		// printf("Did it reach exec_child\n");
		status = check_redir(node);
		if (status != ERRNO_SUCCESS)
			(exit(ERRNO_GENERAL));
		path_status = get_path(node->exp_args[0], vars);
		if (path_status.err.exit_status != ERRNO_SUCCESS)
		{
			status = get_err_msg(path_status.err);
			exit(status);
		}
		if (execve(path_status.cmd_path, node->exp_args, vars->envp) == -1)
			exit(ERRNO_GENERAL);
		// if (path_status.err.errno != 0)
		// 	printf("minishell: %s\n", strerror(path_status.err.errno));
	}
	status = wait_status(pid, vars->env);
	// printf("it reached wait!\n");
	return (status);
}

int	exec_simple_cmd(t_node *node, bool piped, t_minishell *vars)
{
	(void)piped;
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
		status = exec_builtin(node->exp_args, vars->env);
		return(ft_reset_stds(piped, vars), status);
	}
	return (exec_child(node, vars));
}

int	exec_node(t_node *node, bool piped, t_minishell *vars)
{
	int	status;

	expand_node(node, vars);
	// printf("String: %s\n", node->io_list->exp_value[0]);
	// if (!node->io_list->exp_value)
	// 	printf("ITS NULL!\n");
	if (!node)
		return (ERRNO_GENERAL);
	if (node->type == N_PIPE)
		return (exec_pipeline(node, vars));
	else if (node->type == N_AND)
	{
		status = exec_node(node->left, false, vars);
		if (status == ERRNO_SUCCESS)
			return (exec_node(node->right, false, vars));
		return (status);
	}
	else if (node->type == N_OR)
	{
		status = exec_node(node->left, false, vars);
		if (status == ERRNO_SUCCESS)
			return (status);
		return (exec_node(node->right, false, vars));
	}
	else
		return (exec_simple_cmd(node, piped, vars));
	return (ERRNO_GENERAL);
}

int	check_redir(t_node *node)
{
	t_io_node	*temp_io;
	int			status;

	temp_io = node->io_list;
	while (temp_io)
	{
		// printf("String: %s\n", temp_io->exp_value[0]);
		if (temp_io->type == IO_OUT && redir_out(temp_io, &status) != ERRNO_SUCCESS)
			return (status);
		else if (temp_io->type == IO_IN && redir_in(temp_io, &status) != ERRNO_SUCCESS)
			return (status);
		else if (temp_io->type == IO_APPEND && redir_append(temp_io, &status) != ERRNO_SUCCESS)
			return (status);
		else if (temp_io->type == IO_HEREDOC)
		{
			dup2(temp_io->heredoc, STDIN_FILENO);
			close(temp_io->heredoc);
		}
		temp_io = temp_io->next;
	}
	return (ERRNO_SUCCESS);
}

int	redir_out(t_io_node *io_list, int *status)
{
	int	fd;

	if (io_list->exp_value == NULL || io_list->exp_value[1] != NULL)
	{
		*status = get_err_msg((t_err){ERRNO_GENERAL, ERR_MSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		// printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(io_list->exp_value[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		*status = errno;
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = ERRNO_SUCCESS;
	return (*status);
}

int	redir_in(t_io_node *io_list, int *status)
{
	int	fd;

	if (io_list->exp_value == NULL || io_list->exp_value[1] != NULL)
	{
		*status = get_err_msg((t_err){ERRNO_GENERAL, ERR_MSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->exp_value[0], O_RDONLY);
	if (fd == -1)
	{
		// printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(io_list->exp_value[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		*status = 1;
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = ERRNO_SUCCESS;
	return (*status);
}

int	redir_append(t_io_node *io_list, int *status)
{
	int	fd;
	// t_err temp;
	// (void)temp;
	if (io_list->exp_value == NULL || io_list->exp_value[1] != NULL)
	{
		*status = get_err_msg((t_err){ERRNO_GENERAL, ERR_MSG_AMBIGUOUS, io_list->value});
		return (*status);
	}

	fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = 1;
		// printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(io_list->exp_value[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (*status);
	}
	// printf("It's not NULL :(\n");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = ERRNO_SUCCESS;
	return (*status);
	// return (printf("minishell: %s is a directory.\n", io_list->exp_value[0]));
}

// returns -1 on abnormal termination
// returns the exit status of the child process (0-255)
int	wait_status(pid_t pid, t_env *e)
{
	int	status;

	g_wait = 1;
	if (waitpid(pid, &status, 0) == -1)
		return (0);
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		set_val(e, "?", (char *)gb_add(ft_itoa(status)));
	}
	// else
	// {
	// 	status = -1;
	// 	printf("PID %d: terminated abnormally\n", pid);
	// }
	g_wait = 0;
	return (status);
}
