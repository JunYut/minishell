/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:56:00 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:17:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_utoa(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_uint_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while (--len)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	str[0] = (n % 10) + '0';
	return (str);
}

int	ft_print_uint(char *str, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->prec >= 0)
		len += ft_pad_width(flags->prec - 1, ft_strlen(str) - 1, 1);
	len += ft_print_str(str);
	return (len);
}

int	ft_format_uint(char *str, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->left == 1)
		len += ft_print_uint(str, flags);
	if (flags->prec >= 0 && flags->prec < (int)ft_strlen(str))
		flags->prec = ft_strlen(str);
	if (flags->prec >= 0)
	{
		flags->width -= flags->prec;
		len += ft_pad_width(flags->width, 0, 0);
	}
	else
		len += ft_pad_width(flags->width, ft_strlen(str), flags->zero);
	if (flags->left == 0)
		len += ft_print_uint(str, flags);
	return (len);
}

int	ft_print_uintf(unsigned int n, t_flags *flags)
{
	char	*str;
	int		len;

	len = 0;
	if (flags->prec == 0 && n == 0)
	{
		len += ft_pad_width(flags->width, 0, 0);
		return (len);
	}
	str = ft_printf_utoa(n);
	if (!str)
		return (0);
	len += ft_format_uint(str, flags);
	free(str);
	return (len);
}
