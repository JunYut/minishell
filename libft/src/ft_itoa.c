/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 18:41:50 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digits(int n)
{
	size_t	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_get_nbr(char *result, unsigned int n)
{
	if (n <= 9)
		*result = n + '0';
	else
	{
		*result = ((n % 10) + '0');
		ft_get_nbr(result - 1, n / 10);
	}
}

char	*ft_itoa(int n)
{
	char			*result;
	size_t			len;
	unsigned int	nbr;

	nbr = n;
	len = ft_count_digits(n);
	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
	{
		len += 1;
		result = malloc(sizeof(char) * len + 1);
		if (!result)
			return (0);
		nbr *= -1;
		*result = '-';
	}
	else
		result = malloc(sizeof(char) * len + 1);
	ft_get_nbr(result + len - 1, nbr);
	*(result + len) = '\0';
	return (result);
}

/*
int	main(void)
{
	printf("%s\n", ft_itoa(-1));
}
*/
