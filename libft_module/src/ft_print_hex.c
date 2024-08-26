/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:31:38 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:07:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_prefix(int format)
{
	if (format == 'X')
		ft_print_str("0X");
	else
		ft_print_str("0x");
	return (2);
}

char	*ft_printf_xtoa(unsigned int n, int format)
{
	int		nbr;
	int		len;
	char	*str;

	len = ft_hex_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while (--len != -1)
	{
		nbr = n % 16;
		if (nbr < 10)
			str[len] = nbr + '0';
		else if (nbr >= 10 && format == 'x')
			str[len] = (nbr - 10) + 'a';
		else if (nbr >= 10 && format == 'X')
			str[len] = (nbr - 10) + 'A';
		n /= 16;
	}
	return (str);
}

int	ft_print_hex(char *str, int n, int format, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->hash == 1 && n != 0)
		len += ft_print_hex_prefix(format);
	if (flags->prec >= 0)
		len += ft_pad_width(flags->prec - 1, ft_strlen(str) - 1, 1);
	len += ft_print_str(str);
	return (len);
}

int	ft_format_hex(char *str, int n, int format, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->left == 1)
		len += ft_print_hex(str, n, format, flags);
	if (flags->prec >= 0)
	{
		if ((size_t)flags->prec < ft_strlen(str))
			flags->prec = ft_strlen(str);
		flags->width -= flags->prec;
		len += ft_pad_width(flags->width, 0, 0);
	}
	else
		len += ft_pad_width(flags->width, ft_strlen(str)
				+ (flags->hash * 2), flags->zero);
	if (flags->left == 0)
		len += ft_print_hex(str, n, format, flags);
	return (len);
}

int	ft_print_hexf(unsigned int n, int format, t_flags *flags)
{
	char	*str;
	int		len;

	len = 0;
	if (flags->prec == 0 && n == 0)
	{
		len += ft_pad_width(flags->width, 0, 0);
		return (len);
	}
	str = ft_printf_xtoa(n, format);
	if (!str)
		return (0);
	len += ft_format_hex(str, n, format, flags);
	free(str);
	return (len);
}
