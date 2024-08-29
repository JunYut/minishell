/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:29:01 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 11:03:35 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (err.exit_status);
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

t_path	get_path(char *cmd, t_minishell *vars)
{
	char	*full_cmd;

	// if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	// 	return ((t_path){check_exec(cmd, false), cmd});
	full_cmd = parse_path(vars->envp, cmd);
	if (full_cmd != NULL)
		return ((t_path){(t_err){ERRNO_SUCCESS, -1, NULL}, full_cmd});
	return ((t_path){(t_err){ERRNO_NOT_FOUND, ERR_MSG_CMD_NOT_FOUND, cmd}, NULL});
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
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int	exec_simple_cmd(t_node *node, bool piped, t_minishell *vars)
{
	(void)piped;
	return (exec_child(node, vars));
}

int	exec_node(t_node *node, bool piped, t_minishell *vars)
{
	int	status;

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
		printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
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
		*status = 1; //Add a function to handle error messages
		return (*status);
	}
	fd = open(io_list->exp_value[0], O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
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
		*status = 1; //Add a function to handle error messages
		return (*status);
	}
	fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = 1;
		printf("minishell: %s: %s\n", io_list->exp_value[0], strerror(errno)); //Replace with a err handler
		return (*status);
	}
	printf("It's not NULL :(\n");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = ERRNO_SUCCESS;
	return (*status);
	// return (printf("minishell: %s is a directory.\n", io_list->exp_value[0]));
}
