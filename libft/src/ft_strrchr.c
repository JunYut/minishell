/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:31:07 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/19 19:43:20 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	while (slen != 0 && *(s + slen) != (unsigned char)c)
		slen--;
	if (*(s + slen) == (unsigned char)c)
		return ((char *)(s + slen));
	return (0);
}
/*
int	main(void)
{
	char *str = "Hello";
	char *result = ft_strrchr(str, 'H' + 1234);
	char *result2 = strrchr(str, 'H' + 1234);

	printf("%s\n", result);
	printf("%s\n", result2);
}
*/
