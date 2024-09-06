/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:51:35 by we                #+#    #+#             */
/*   Updated: 2024/09/06 13:13:10 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (io_list->exp_value == NULL || io_list->exp_value[1] != NULL)
	{
		*status = get_err_msg((t_err){ERRNO_GENERAL, ERR_MSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(io_list->exp_value[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = ERRNO_SUCCESS;
	return (*status);
}

void	ft_reset_stds(bool piped, t_minishell *vars)
{
	if (piped)
		return ;
	dup2(vars->stdin, 0);
	dup2(vars->stdout, 1);
}
