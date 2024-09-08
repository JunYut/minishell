/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:13:22 by we                #+#    #+#             */
/*   Updated: 2024/09/08 13:20:23 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

bool	is_valid_regex(char *str)
{
	if (!str || *str == '\'' || *str == '"' || !*str)
		return (false);
	return (is_in_set('*', str));
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}
