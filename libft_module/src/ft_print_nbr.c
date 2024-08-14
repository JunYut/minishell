/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:45:12 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:07:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_itoa(long n)
{
	int		len;
	char	*str;

	len = ft_itoa_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (--len)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (str[0] != '-')
		str[0] = (n % 10) + '0';
	return (str);
}

int	ft_print_sign(int n, t_flags *flags)
{
	int	len;

	len = 0;
	if (n < 0 && flags->prec == -1)
	{
		len += ft_print_char('-');
		flags->width--;
	}
	else if (flags->plus == 1)
		len += ft_print_char('+');
	else if (flags->space == 1)
	{
		len += ft_print_char(' ');
		flags->width--;
	}
	return (len);
}

int	ft_print_nbr(char *str, int n, t_flags *flags)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (flags->zero == 0 || flags->prec >= 0)
			len += ft_print_char('-');
	}
	else if (flags->plus == 1 && flags->zero == 0)
		len += ft_print_char('+');
	else if (flags->space == 1 && flags->zero == 0)
		len += ft_print_char(' ');
	if (flags->prec >= 0)
		len += ft_pad_width(flags->prec - 1, ft_strlen(str) - 1, 1);
	len += ft_print_str(str);
	return (len);
}

int	ft_format_nbr(char *str, int n, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->zero == 1)
		len += ft_print_sign(n, flags);
	if (flags->left == 1)
		len += ft_print_nbr(str, n, flags);
	if (flags->prec >= 0 && (size_t)flags->prec < ft_strlen(str))
		flags->prec = ft_strlen(str);
	if (flags->prec >= 0)
	{
		flags->width -= flags->prec;
		if (n < 0 && flags->left == 0 && flags->zero == 1)
			flags->width -= 1;
		len += ft_pad_width(flags->width, 0, 0);
	}
	else
		len += ft_pad_width(flags->width - flags->plus
				- flags->space, ft_strlen(str), flags->zero);
	if (flags->left == 0)
		len += ft_print_nbr(str, n, flags);
	return (len);
}

int	ft_print_nbrf(int n, t_flags *flags)
{
	char	*str;
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		if (flags->zero == 0)
			flags->width--;
	}
	if (flags->prec == 0 && n == 0)
	{
		len += ft_pad_width(flags->width, 0, 0);
		return (len);
	}
	str = ft_printf_itoa(nb);
	if (!str)
		return (0);
	len += ft_format_nbr(str, n, flags);
	free(str);
	return (len);
}
