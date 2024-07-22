/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_delim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:15 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/20 14:55:58 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_delim(char *s1, char *s2, char *delim)
{
	char	*new_str;
	int		total_length;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!delim || !*delim || *s1 == '\0')
		return (gnl_strjoin(s1, s2));
	total_length = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(delim) + 1;
	new_str = ft_calloc(total_length, 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = -1;
	while (delim[++j])
		new_str[i++] = delim[j];
	j = -1;
	while (s2[++j])
		new_str[i++] = s2[j];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}
