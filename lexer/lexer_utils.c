/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:32:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/16 13:20:47 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_quote_closed(char *line, int	*i)
{
	char	quote_type;

	quote_type = line[*i];
	if (ft_strchr(line + *i + 1, quote_type))
	{
		(*i)++;
		while ((line[*i]) != quote_type)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

void	skip_quote_string(char *line, int *i)
{
	char	quote_type;

	quote_type = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote_type)
		(*i)++;
	(*i)++;
}
