/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:08:48 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/03/22 14:01:52 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	ft_init_flags(void)
{
	t_flags	flags;

	flags.left = 0;
	flags.zero = 0;
	flags.prec = -1;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.width = 0;
	flags.spec = 0;
	return (flags);
}

int	ft_isspec(int c)
{
	if (ft_strchr("cspdiuxX%", c))
		return (1);
	return (0);
}

int	ft_isflag(int c)
{
	if (ft_strchr("-0.# +", c))
		return (1);
	return (0);
}

int	ft_isformat(int c)
{
	if (ft_isdigit(c) || ft_isspec(c) || ft_isflag(c))
		return (1);
	return (0);
}

int	ft_flag_precision(const char *str, int pos, t_flags *flags)
{
	flags->prec = 0;
	while (ft_isdigit(str[pos]))
		flags->prec = (flags->prec * 10) + (str[pos++] - '0');
	return (pos);
}
