/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:32:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/26 18:23:40 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skip_spaces(char **line)
{
	while(**line && is_space(**line))
		(*line)++;
}

int	is_seperator(char c)
{
	if (is_space(c) || c == '>' || c == '<' || c == '|' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_in_set(char c, char *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
