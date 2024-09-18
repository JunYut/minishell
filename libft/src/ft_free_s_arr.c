/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_s_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:16:25 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/18 16:32:54 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_s_arr(char **arr)
{
	char	**tmp;

	if (arr == NULL)
		return ;
	tmp = arr;
	while (*tmp != 0)
		free(*(tmp++));
	free(arr);
}
