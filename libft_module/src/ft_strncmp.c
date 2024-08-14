/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:30:23 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/23 19:58:44 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u_s1;
	unsigned char	u_s2;

	while (n-- > 0)
	{
		u_s1 = (unsigned char)*s1++;
		u_s2 = (unsigned char)*s2++;
		if (u_s1 != u_s2)
			return (u_s1 - u_s2);
	}
	return (0);
}
/*
int	main(void)
{
	int	result = ft_strncmp("Hello", "Hello World", 7);
	int	result2 = strncmp("Hello", "Hello World", 7);
	printf("%d\n", result);
	printf("%d\n", result2);
}
*/
