/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:32:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 10:27:42 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skip_spaces(char **line)
{
	while (**line && is_space(**line))
		(*line)++;
}

int	is_seperator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || is_space(*s) || *s == '>' || *s == '<'
		|| *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

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
	while (line[*i] != quote_type)
		(*i)++;
	(*i)++;
}
