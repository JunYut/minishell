/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:50:19 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/17 16:00:11 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	find_pos(char *str, char delim)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != delim)
		;
	if (str[i] != delim)
		return (-1);
	return (i);
}

char	*ft_strndup(char *str, int pos)
{
	char	*dup;

	if (pos < 1)
		return (NULL);
	dup = malloc(pos + 1);
	ft_strncpy(dup, str, pos);
	return (dup);
}

void	ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}
