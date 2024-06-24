/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:23:41 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/19 21:44:50 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*buffer;

	slen = ft_strlen(s);
	buffer = (char *)malloc(sizeof(char) * (slen + 1));
	if (!buffer)
		return (0);
	slen = 0;
	while (s[slen])
	{
		buffer[slen] = s[slen];
		slen++;
	}
	buffer[slen] = '\0';
	return (buffer);
}
