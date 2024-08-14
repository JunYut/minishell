/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 18:36:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;

	if ((!dst || !src) && size == 0)
		return (0);
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen > size)
		dstlen = size;
	if (dstlen == size)
		return (size + srclen);
	if (srclen < size - dstlen)
	{
		ft_memcpy(dst + dstlen, src, srclen);
		dst[dstlen + srclen] = '\0';
	}
	else
	{
		ft_memcpy(dst + dstlen, src, size - dstlen - 1);
		dst[size - 1] = '\0';
	}
	return (dstlen + srclen);
}
/*
int	main(void)
{
	char	dst[20] = "Hello, ";
	char	*src = "World!";
	size_t	result = ft_strlcat(dst, src, sizeof(dst));
	size_t	result2 = strlcat(dst, src, sizeof(dst));

	printf("Result: %zu\n", result);
	printf("Result2: %zu\n", result2);
	printf("Destination: %s\n", dst);
	return (0);
}
*/
