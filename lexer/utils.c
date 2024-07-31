/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:32:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/31 18:28:05 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (is_space(*s) || !ft_strncmp(s, "&&", 2) || *s == '>' || *s == '<'
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
