/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:48:46 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 18:38:21 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndl_len;

	if ((!haystack || !needle) && len == 0)
		return (0);
	ndl_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len-- >= ndl_len)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, ndl_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (0);
}
