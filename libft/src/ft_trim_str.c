/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:08:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/11 21:22:39 by kkhai-ki         ###   ########.fr       */
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
	result = ft_substr(str, 0, len);
	if (!result)
		return (0);
	return (result);
}
