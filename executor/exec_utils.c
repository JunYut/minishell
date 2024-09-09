/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:55:04 by we                #+#    #+#             */
/*   Updated: 2024/09/09 13:10:28 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path	get_path(char *cmd, t_minishell *vars)
{
	char	*full_cmd;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){check_exec(cmd), cmd});
	if (*cmd == '\0')
		return ((t_path){(t_err){ERRNO_NOT_FOUND, ERR_MSG_CMD_NOT_FOUND, "''"},
			NULL});
	full_cmd = parse_path(vars->env->envp, cmd);
	if (full_cmd != NULL)
		return ((t_path){(t_err){ERRNO_SUCCESS, -1, NULL}, full_cmd});
	return ((t_path){(t_err){ERRNO_NOT_FOUND,
		ERR_MSG_CMD_NOT_FOUND, cmd}, NULL});
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
		print_err(err.cause, "Permission denied");
		return (err.exit_status);
	}
	else if (errno == 21)
	{
		print_err(err.cause, strerror(errno));
		return (ERRNO_CANT_EXEC);
	}
	else if (errno == 2)
	{
		print_err(err.cause, strerror(errno));
		return (ERRNO_NOT_FOUND);
	}
	return (err.exit_status);
}

t_err	check_exec(char *file)
{
	int	fd;

	(void)fd;
	if (!*file)
		return ((t_err){ERRNO_GENERAL, ERR_MSG_NO_SUCH_FILE, file});
	fd = open(file, O_WRONLY);
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
		set_val(e, "?", gbc_itoa(status));
	}
	g_wait = 0;
	return (status);
}
