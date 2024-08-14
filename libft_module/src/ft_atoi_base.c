/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:55:25 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/04/24 17:05:58 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_base(char *base)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (base[i] != '\0')
	{
		j = 0;
		while (j < i)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		if (base[i] == '+' || base[i] == '-')
			return (0);
		else if (base[i] == ' ' || (base[i] >= 9 && base[i] <= 13))
			return (0);
		i++;
		count++;
	}
	return (count);
}

static int	base_index(char *base, char c)
{
	int	index;

	index = 0;
	while (base[index] != '\0')
	{
		if (base[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	result;
	int	base_len;
	int	index;

	result = 0;
	base_len = count_base(base);
	if (base_len < 2)
		return (0);
	while (*str != '\0')
	{
		if (ft_isalpha(*str))
			*str = ft_toupper(*str);
		index = base_index(base, *str);
		if (index == -1)
			return (result);
		result = (result * base_len) + index;
		str++;
	}
	return (result);
}
