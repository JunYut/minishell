/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:14:40 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/06/24 14:29:54 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(const char *const argv[])
{
	int	is_n;
	int	i;

	if (!argv)
	{
		printf("\n");
		return;
	}
	is_n = 1;
	if (argv[0] && ft_strcmp(argv[0], "-n") == 0)
	{
		is_n = 0;
		++argv;
	}
	i = -1;
	while (argv[++i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
	}
	if (is_n)
		printf("\n");
}
