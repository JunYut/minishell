/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:18:21 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/18 16:02:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	**split_args(char *str)
{
	char	**args;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	if (!word_count)
		return (NULL);
	args = ft_calloc(word_count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args = allocate_args(str, args);
	if (!args)
		return (ft_free_s_arr(args), NULL);
	return (fill_args(str, args));
}

char	**allocate_args(char *str, char **args)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			start = i;
			skip_word(str, &i);
			args[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!args[j])
				return (NULL);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (args);
}

char	**fill_args(char *str, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			fill_word(str, args, &i, j);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (args);
}

void	fill_word(char *str, char **args, int *i, int j)
{
	char	quote;
	int		k;

	k = 0;
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			args[j][k++] = str[(*i)++];
		else
		{
			quote = str[(*i)++];
			args[j][k++] = quote;
			while (str[*i] != quote)
				args[j][k++] = str[(*i)++];
			args[j][k++] = str[(*i)++];
		}
	}
}
