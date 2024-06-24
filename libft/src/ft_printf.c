/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:38:57 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/22 14:02:14 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(va_list args, const char format, t_flags *flags)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_cf(va_arg(args, int), flags);
	else if (format == 's')
		len += ft_print_sf(va_arg(args, char *), flags);
	else if (format == 'p')
		len += ft_print_ptrf(va_arg(args, unsigned long), flags);
	else if (format == 'd' || format == 'i')
		len += ft_print_nbrf(va_arg(args, int), flags);
	else if (format == 'u')
		len += ft_print_uintf(va_arg(args, unsigned int), flags);
	else if (format == 'x' || format == 'X')
		len += ft_print_hexf(va_arg(args, unsigned int), format, flags);
	else if (format == '%')
		len += ft_print_cf('%', flags);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if (!format || *format == '\0')
		return (0);
	va_start(args, format);
	len = ft_parsing(format, args);
	va_end(args);
	return (len);
}
