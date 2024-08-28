/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:24:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/28 11:25:29 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gbc.h"

t_list	*gb_lstnew(void *content)
{
	return (gb_add(ft_lstnew(content)));
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
