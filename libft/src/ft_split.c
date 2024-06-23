/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:22:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2023/10/22 20:40:06 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		word_count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (word_count);
}

static char	*ft_strndup(char const *s, size_t n)
{
	size_t	i;
	char	*result;

	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (0);
	i = -1;
	while (++i < n)
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

static void	ft_free_arr(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (0);
	word_count = ft_count_word(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (0);
	i = -1;
	while (++i < word_count)
	{
		while (*s && *s == c)
			s++;
		result[i] = ft_strndup(s, ft_wordlen(s, c));
		if (!result[i])
		{
			ft_free_arr(result, i - 1);
			return (0);
		}
		s += ft_wordlen(s, c);
	}
	result[word_count] = 0;
	return (result);
}
