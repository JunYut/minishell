/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:31:17 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/06/24 13:29:26 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Should go to home if NULL
int	cd(const char *path)
{
	if (!path)
		chdir(getenv("HOME"));
	else if(chdir(path))
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
