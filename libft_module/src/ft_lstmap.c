/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:58:53 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 20:48:21 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*result;
	t_list	*buffer;

	if (!lst || !f || !del)
		return (0);
	result = ft_lstnew(f(lst->content));
	if (!result)
		return (0);
	buffer = result;
	lst = lst->next;
	while (lst)
	{
		buffer->next = ft_lstnew(f(lst->content));
		if (!buffer->next)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		buffer = buffer->next;
		lst = lst->next;
	}
	return (result);
}
