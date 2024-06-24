/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:53:03 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 20:46:50 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		buffer = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = buffer;
	}
	*lst = 0;
}
