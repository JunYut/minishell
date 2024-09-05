/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:02:08 by we                #+#    #+#             */
/*   Updated: 2024/09/05 16:29:46 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	print_builtin_err(char *builtin, char *cause, char *error)
{
	if (!cause)
		return (0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(cause, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	print_err(char *cause, char *error)
{
	if (!cause)
		return (0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cause, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}

void	print_tree(t_node *node, int depth, char *branch)
{
	int	i;

	if (depth != 0)
		printf("├─");
	i = -1;
	while (++i < depth)
		printf("─");
	printf("Node(%s): %s | Value: %s\n",
		branch, get_node_type(node->type), node->args);
}

void	show_tree(t_node *node, int depth, char *branch)
{
	if (node == NULL)
		return ;
	print_tree(node, depth, branch);
	show_tree(node->left, depth + 1, "left");
	show_tree(node->right, depth + 1, "right");
}
