/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:48:57 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/23 13:47:17 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	if (size != 0 && (count > UINT_MAX / size))
		return (0);
	buffer = malloc((count * size));
	if (!buffer)
		return (0);
	ft_bzero(buffer, (count * size));
	return (buffer);
}
