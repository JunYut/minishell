/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:41:55 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:11:49 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (write (1, str, len));
}

int	ft_print_s_prec(const char *str, int prec)
{
	int	len;

	len = 0;
	while (str[len] && len < prec)
		write(1, &str[len++], 1);
	return (len);
}

int	ft_format_str(const char *str, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->prec >= 0)
	{
		len += ft_pad_width((size_t)flags->prec, ft_strlen(str), 0);
		len += ft_print_s_prec(str, flags->prec);
	}
	else
		len += ft_print_str((char *)str);
	return (len);
}

int	ft_print_sf(const char *str, t_flags *flags)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	if (flags->prec >= 0 && (size_t)flags->prec > ft_strlen(str))
		flags->prec = ft_strlen(str);
	if (flags->left == 1)
		len += ft_format_str(str, flags);
	if (flags->prec >= 0)
		len += ft_pad_width(flags->width, flags->prec, 0);
	else
		len += ft_pad_width(flags->width, ft_strlen(str), 0);
	if (flags->left == 0)
		len += ft_format_str(str, flags);
	return (len);
}
