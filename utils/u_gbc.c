/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_gbc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:24:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 16:50:45 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*gbc_lstnew(void *content)
{
	return (gbc_add(ft_lstnew(content)));
}

char	*gbc_itoa(int n)
{
	return (gbc_add(ft_itoa(n)));
}

char	*gbc_strdup(const char *s1)
{
	return (gbc_add(ft_strdup(s1)));
}

t_wc_type	*gbc_newtoken(t_wc_type token)
{
	t_wc_type	*new;

	new = gbc_malloc(sizeof(t_token));
	*new = token;
	return (new);
}
