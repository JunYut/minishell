/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 18:43:56 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **av)
{
	int	nl;
	int	i;

	nl = 1;
	if (av && av[0])
	{
		if (ft_strcmp(av[0], "-n") == 0)
		{
			nl = 0;
			av++;
		}
		i = -1;
		while (av[++i])
		{
			// printf("%s", av[i]);
			ft_putstr_fd(av[i], STDOUT_FILENO);
			if (av[i + 1])
				// printf(" ");
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
	}
	if (nl)
		// printf("\n");
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
