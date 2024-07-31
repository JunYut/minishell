/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:08:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/31 18:04:11 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_str(char *str, char delim)
{
	char	*result;
	int		len;

	while (*str && is_in_set(delim, str) == 0)
		str++;
	len = ft_strlen(str);
	while (len != 0 && is_in_set(str[len - 1], &delim) == 0)
		len--;
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	result = ft_substr(str, 0, len);
	return (result);
}
