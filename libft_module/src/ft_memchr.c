/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:29:52 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/18 16:25:01 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*buffer;

	buffer = (const unsigned char *)s;
	while (n-- > 0)
	{
		if (*buffer == (unsigned char)c)
			return ((void *)buffer);
		buffer++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s = "ABCDEFGHIJKLMNOPQRSTUVWYXZ";
	void	*result = ft_memchr(s, 'Q', 26);
	void	*result2 = memchr(s, 'Q', 26);
	printf("%p and %p\n", result, result2);
}
*/
