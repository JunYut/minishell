/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:18:21 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/07 21:17:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_args(char *str)
{
	char	**result;
	// char	*str2;
	int		count;
	// int		i;

	if (!str)
		return (NULL);
	count = count_words(str);
	result = ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (free(str), NULL);
	// i = -1;
	// while (++i < count)
	// 	result[i] = ft_calloc(quoted_len() + 1, sizeof(char));
	// printf("String: %s\n", str);
	printf("Count: %d\n", count);
	return (NULL);
}

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

// char	*fill_word(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 	{

// 	}

// }

// char	*quoted_len(char *str)
// {
// 	char	quote;
// 	int		i;

// 	quote = *str;
// 	i = 1;
// 	while (str[i] && str[i] != quote)
// 		i++;
// 	return (i - 1);
// }
