/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:09:56 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/10 15:08:37 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline(t_node *node, t_minishell *vars)
{
	int		status;
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	pipe(fd);
	pid_left = fork();
	if (pid_left == 0)
		exec_pipe_child(node->left, fd, NODE_LEFT, vars);
	else
	{
		pid_right = fork();
		if (pid_right == 0)
			exec_pipe_child(node->right, fd, NODE_RIGHT, vars);
		else
		{
			close(fd[0]);
			close(fd[1]);
			status = wait_status(pid_left, vars->env);
			status = wait_status(pid_right, vars->env);
			return (status);
		}
	}
	return (ERRNO_SUCCESS);
}

void	exec_pipe_child(t_node *node, int *fd, int direction, t_minishell *vars)
{
	int	status;

	if (direction == NODE_LEFT)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (direction == NODE_RIGHT)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = exec_node(node, true, vars);
	clear(vars);
	exit(status);
}
