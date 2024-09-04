/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:24:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 09:48:02 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gbc.h"

t_list	*gb_lstnew(void *content)
{
	return (gb_add(ft_lstnew(content)));
}

char	*gb_itoa(int n)
{
	return (gb_add(ft_itoa(n)));
}

char	*gb_strdup(const char *s1)
{
	return (gb_add(ft_strdup(s1)));
}

t_wc_type	*gb_newtoken(t_wc_type token)
{
	t_wc_type	*new;

	new = gb_malloc(sizeof(t_token));
	*new = token;
	return (new);
}
