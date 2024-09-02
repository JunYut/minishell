/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/02 10:42:34 by tjun-yu          ###   ########.fr       */
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
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
		}
	}
	if (nl)
		printf("\n");
	return (0);
}
