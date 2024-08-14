/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:54:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/05 15:16:22 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_adr(unsigned long n)
{
	if (n >= 16)
	{
		ft_print_adr(n / 16);
		ft_print_adr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_print_char(n + '0');
		else if (n > 9)
			ft_print_char((n - 10) + 'a');
	}
}

int	ft_print_ptr(unsigned long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		len += ft_print_str(NULLPTR);
		return (len);
	}
	len += ft_print_str("0x");
	ft_print_adr(ptr);
	len += ft_ptr_len(ptr);
	return (len);
}

int	ft_print_ptrf(unsigned long ptr, t_flags *flags)
{
	int	len;

	len = 0;
	if (!ptr)
		flags->width -= ft_strlen(NULLPTR) - 1;
	else
		flags->width -= 2;
	if (flags->left == 1)
		len += ft_print_ptr(ptr);
	len += ft_pad_width(flags->width, ft_ptr_len(ptr), 0);
	if (flags->left == 0)
		len += ft_print_ptr(ptr);
	return (len);
}
