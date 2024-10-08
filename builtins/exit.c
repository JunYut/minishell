/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:06:53 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/12 12:22:39 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char **argv, int status, t_minishell *vars)
{
	int	exit_status;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv && argv[0])
	{
		if (!is_numeric(argv[0]))
		{
			print_builtin_err("exit", argv[0], "numeric argument required");
			exit_status = 2;
		}
		else if (count_args(argv, "exit") > 1)
			exit_status = 1;
		else
			exit_status = ft_atoi(argv[0]);
	}
	if (!argv || !argv[0] || argv[0][0] == '\0')
		exit_status = status;
	clear(vars);
	exit(exit_status);
}

int	is_numeric(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}
