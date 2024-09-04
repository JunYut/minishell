/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:06:53 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 12:44:33 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char **status, t_env *e)
{
	int	exit_status;

	printf("exit\n");
	if (status && status[0])
	{
		if (!is_numeric(status[0]))
		{
			print_builtin_err("exit", status[0], "numeric argument required");
			exit_status = 2;
		}
		else if (count_args(status, "exit", e) > 1)
			exit_status = 1;
		else
			exit_status = ft_atoi(status[0]);
	}
	if (!status || !status[0] || status[0][0] == '\0')
		exit_status = ft_atoi(fetch_val("?", e));
	gb_clear();
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
