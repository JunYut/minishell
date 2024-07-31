/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:03:39 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/23 20:19:32 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*u_dst;
	const unsigned char	*u_src;

	u_dst = dst;
	u_src = src;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		u_dst += len;
		u_src += len;
		while (len-- > 0)
			*--u_dst = *--u_src;
	}
	else
		while (len-- > 0)
			*u_dst++ = *u_src++;
	return (dst);
}
