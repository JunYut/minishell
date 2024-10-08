/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:55:04 by we                #+#    #+#             */
/*   Updated: 2024/09/25 14:32:28 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_shlvl(t_minishell *vars)
{
	char	*shlvl;
	int		tmp;

	tmp = ft_atoi(fetch_val("SHLVL", vars->env));
	shlvl = ft_itoa(tmp + 1);
	set_val(vars->env, "SHLVL", shlvl);
	free(shlvl);
	return (0);
}

int	get_err_msg(t_err err)
{
	if (err.msg == ERR_MSG_CMD_NOT_FOUND)
		print_err(err.cause, "command not found");
	else if (err.msg == ERR_MSG_AMBIGUOUS)
		ft_putstr_fd("minishell: *: ambiguous redirect\n", 2);
	else if (err.msg == ERR_MSG_PERM_DENIED)
		print_err(err.cause, "Permission denied");
	else if (err.msg == ERR_MSG_IS_DIR)
		print_err(err.cause, "Is a directory");
	else if (err.msg == ERR_MSG_NO_SUCH_FILE)
		print_err(err.cause, "No such file or directory");
	return (err.exit_status);
}

t_err	check_exec(char *file)
{
	int	fd;
	int	open_errno;

	if (!*file)
		return ((t_err){ERRNO_GENERAL, ERR_MSG_NO_SUCH_FILE, file});
	fd = open(file, O_WRONLY);
	open_errno = errno;
	close(fd);
	if (open_errno == 21)
		return ((t_err){ERRNO_IS_DIR, ERR_MSG_IS_DIR, file});
	else if (open_errno == 2)
		return ((t_err){ERRNO_NOT_FOUND, ERR_MSG_NO_SUCH_FILE, file});
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

// returns -1 on abnormal termination
// returns the exit status of the child process (0-255)
int	wait_status(pid_t pid)
{
	int	status;

	g_wait = 1;
	if (waitpid(pid, &status, 0) == -1)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			return (131);
		else if (WTERMSIG(status) == SIGINT)
			return (130);
	}
	else if (WIFEXITED(status))
		init_vars(NULL, NULL)->exit_status = WEXITSTATUS(status);
	g_wait = 0;
	return (WEXITSTATUS(status));
}
