/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:24:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:01:50 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gbc.h"

t_list	*gb_lstnew(void *content)
{
	return (gbc_add(ft_lstnew(content)));
}

char	*gb_itoa(int n)
{
	return (gbc_add(ft_itoa(n)));
}

char	*gb_strdup(const char *s1)
{
	return (gbc_add(ft_strdup(s1)));
}

t_wc_type	*gb_newtoken(t_wc_type token)
{
	t_wc_type	*new;

	new = gbc_malloc(sizeof(t_token));
	*new = token;
	return (new);
}
