/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:19:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/17 14:01:10 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
	{
		ft_memcpy(dst, src, srclen);
		dst[srclen] = '\0';
	}
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}
/*
int	main(void)
{
	char	dst[5];
	char	*src = "Hello";
	size_t	dstsize = sizeof(dst);
	printf("%zu\n", ft_strlcpy(dst, src, dstsize));
	printf("%s\n", dst);
	printf("%zu", strlcpy(dst, src, dstsize));
}
*/
