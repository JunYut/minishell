/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:58:03 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/19 18:48:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_temp;
	unsigned const char	*src_temp;

	if (!dst && !src)
		return (0);
	dst_temp = dst;
	src_temp = src;
	while (n-- > 0)
		*dst_temp++ = *src_temp++;
	return (dst);
}
/*
int main(void)
{
    unsigned char src_buffer[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned char dst_buffer[50];

    ft_memcpy(dst_buffer, src_buffer, sizeof(src_buffer));
    printf("Copied data: %s\n", dst_buffer);
    return (0);
}
*/
