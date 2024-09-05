/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tokenize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:10:16 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:04:10 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

// Returns an array of tokens terminated by T_END
t_wc_type	*tokenize_wc(char *regex)
{
	t_wc_type	*token;
	int			i;
	int			j;

	token = gbc_malloc(sizeof(t_wc_type) * (count_token(regex) + 1));
	j = -1;
	i = -1;
	while (regex[++i])
	{
		if (regex[i] == '*')
		{
			token[++j] = WC_WILDCARD;
			while (regex[i + 1] && regex[i + 1] == '*')
				++i;
		}
		else
		{
			token[++j] = WC_PATTERN;
			while (regex[i + 1] && regex[i + 1] != '*')
				++i;
		}
	}
	token[++j] = WC_END;
	return (token);
}

int	count_token(char *regex)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (regex[++i])
	{
		++count;
		if (regex[i] == '*')
			while (regex[i + 1] && regex[i + 1] == '*')
				++i;
		else
			while (regex[i + 1] && regex[i + 1] != '*')
				++i;
	}
	return (count);
}
