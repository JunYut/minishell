/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:25:30 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/18 16:44:09 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;

	u_s1 = (const unsigned char *)s1;
	u_s2 = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*u_s1 != *u_s2)
			return (*u_s1 - *u_s2);
		u_s1++;
		u_s2++;
	}
	return (0);
}
