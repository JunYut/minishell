/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:34:45 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:07:15 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	return (write (1, &c, 1));
}

int	ft_pad_width(int width, int size, int zero)
{
	int	len;

	len = 0;
	while (width - size > 0)
	{
		if (zero != 0)
			len += ft_print_char('0');
		else
			len += ft_print_char(' ');
		width--;
	}
	return (len);
}

int	ft_print_cf(int c, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->left == 1)
		len += ft_print_char(c);
	len += ft_pad_width(flags->width, 1, flags->zero);
	if (flags->left == 0)
		len += ft_print_char(c);
	return (len);
}
