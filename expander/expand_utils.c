/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:13:22 by we                #+#    #+#             */
/*   Updated: 2024/09/09 11:19:12 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	quote;

	if (!str || !*str)
		return (ft_strdup(""));
	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		if (str[i] == quote)
			j++;
	}
	new_str = ft_calloc(ft_strlen(str) - j + 1, sizeof(char));
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != quote)
			new_str[j++] = str[i];
	free(str);
	return (new_str);
}

bool	is_valid_regex(char *str)
{
	if (!str || *str == '\'' || *str == '"' || !*str)
		return (false);
	return (is_in_set('*', str));
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}
