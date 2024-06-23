/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:54:23 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/11/09 14:25:15 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	limit;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	limit = ft_strlen(s + start);
	if (len > limit)
		len = limit;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	ft_memcpy(result, (char *)(s + start), len);
	result[len] = '\0';
	return (result);
}
/*
int main(void)
{
	ft_substr(NULL, 0, 12);
}
*/
