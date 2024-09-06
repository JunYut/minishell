/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:47:26 by we                #+#    #+#             */
/*   Updated: 2024/09/06 15:47:45 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	skip_word(char *str, int *i)
{
	char	quote;

	quote = 0;
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			(*i)++;
		else
		{
			quote = str[(*i)++];
			while (str[*i] != quote)
				(*i)++;
			(*i)++;
		}
	}
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			skip_word(str, &i);
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (count);
}
