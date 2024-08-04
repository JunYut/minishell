/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:20:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/04 16:30:49 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_store_str(int fd, char *stored)
{
	char	*buffer;
	int		i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	i = 1;
	while (!gnl_has_newline(stored) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[i] = '\0';
		stored = gnl_strjoin(stored, buffer);
	}
	free(buffer);
	return (stored);
}

char	*ft_get_line(char *stored)
{
	int		i;
	char	*str;

	i = 0;
	if (!*stored)
		return (0);
	while (stored[i] && stored[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		str[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
	{
		str[i] = stored[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_new_stored(char *stored)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (0);
	}
	str = malloc(sizeof(char) * (ft_strlen(stored) - i + 1));
	if (!str)
		return (0);
	i++;
	j = 0;
	while (stored[i])
		str[j++] = stored[i++];
	str[j] = '\0';
	free(stored);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*stored[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (0);
	stored[fd] = ft_store_str(fd, stored[fd]);
	if (!stored[fd])
		return (0);
	line = ft_get_line(stored[fd]);
	stored[fd] = ft_get_new_stored(stored[fd]);
	return (line);
}
