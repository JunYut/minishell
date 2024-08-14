/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:17:07 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/22 14:02:08 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parsing(const char *str, va_list args)
{
	int		i;
	int		len;
	t_flags	flags;

	i = -1;
	len = 0;
	while (str[++i])
	{
		flags = ft_init_flags();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i = ft_parse_flags(str, i, &flags);
			if (str[i] != '\0' && flags.spec > 0)
				len += ft_print_format(args, flags.spec, &flags);
			else if (str[i] != '\0')
				len += ft_print_char(str[i]);
		}
		else
			len += ft_print_char(str[i]);
	}
	return (len);
}

int	ft_parse_flags(const char *str, int i, t_flags *flags)
{
	while (str[++i] && ft_isformat(str[i]))
	{
		if (str[i] == '-')
			flags->left = 1;
		if (str[i] == '0' && flags->left == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = ft_flag_precision(str, i + 1, flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (ft_isdigit(str[i]))
			flags->width = flags->width * 10 + (str[i] - '0');
		if (ft_isspec(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}
