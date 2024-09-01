/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:06:53 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 14:08:28 by kkhai-ki         ###   ########.fr       */
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
			printf("minishell: exit: %s: numeric argument required\n", status[0]);
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
	int i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}
