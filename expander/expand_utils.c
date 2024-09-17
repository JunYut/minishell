/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:13:22 by we                #+#    #+#             */
/*   Updated: 2024/09/17 10:29:12 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*remove_outer_quotes(char *str)
{
	char	*result_str;
	int		result_len;
	int		len;

	len = ft_strlen(str);
	result_len = find_result_len(str, len);
	result_str = build_result_string(str, len, result_len);
	// free(str);
	return (result_str);
}

char	*build_result_string(char *input, int len, int result_len)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = malloc(result_len + 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (i < len && input[i] != quote)
				result[j++] = input[i++];
		}
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	find_result_len(char *input, int len)
{
	char	quote;
	int		result_len;
	int		i;

	result_len = 0;
	i = 0;
	while (i < len)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (i < len && input[i] != quote)
			{
				result_len++;
				i++;
			}
		}
		else
			result_len++;
		i++;
	}
	return (result_len);
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
