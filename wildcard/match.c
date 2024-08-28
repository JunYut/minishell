/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:09:27 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/28 11:23:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "wildcard.h"

t_list	*ent_match(t_wildcard *wc, char *regex)
{
	t_list	*match_lst;
	t_list	*lst;
	char	*match;

	lst = wc->dirent->files;
	if (regex[0] == '.')
		lst = wc->dirent->dot_files;
	match_lst = NULL;
	while (lst)
	{
		match = pattern_match(lst->content, wc->token, wc->pattern);
		// DPRINTF("match: %s\n\n", match);
		if (match)
			ft_lstadd_back(&match_lst, gb_lstnew(gb_strdup(match)));
		lst = lst->next;
	}
	return (match_lst);
}

// returns the matched string or NULL if it doesn't match
char	*pattern_match(char *ent, t_wc_type *token, char **pattern)
{
	char	*pos;
	char	*tmp;
	int		i;
	int		j;

	tmp = ent;
	j = -1;
	i = -1;
	while (token[++i] != WC_END)
	{
		if (token[i] == WC_PATTERN)
		{
			pos = ft_strnstr(tmp, pattern[++j], ft_strlen(tmp));
			if (token[i + 1] == WC_END)
				pos = r_strnstr(tmp, pattern[j], ft_strlen(tmp));
			if (!pos || (i == 0 && pos != ent))
				return (NULL);
			tmp = pos + ft_strlen(pattern[j]);
			if (token[i + 1] == WC_END && *tmp != '\0')
				return (NULL);
		}
	}
	return (ent);
}

char	*r_strnstr(char *haystack, char *needle, size_t len)
{
	char	*pos;
	size_t	ndl_len;

	if ((!haystack || !needle) && len == 0)
		return (0);
	pos = NULL;
	ndl_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len-- >= ndl_len)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, ndl_len) == 0)
			pos = (char *)haystack;
		haystack++;
	}
	return (pos);
}
