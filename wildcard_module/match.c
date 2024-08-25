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
char	*pattern_match(char *ent, t_token *token, char **pattern)
{
	char	*pos;
	char	*tmp;
	int		i;
	int		j;

	tmp = ent;
	j = -1;
	i = -1;
	while (token[++i])
	{
		if (token[i] == T_PATTERN)
		{
			if (token[i + 1] == T_END && *tmp != '\0')
				return (NULL);
			pos = ft_strnstr(tmp, pattern[++j], ft_strlen(tmp));
			if (!pos)
				return (NULL);
		}
		if (token[i + 1] == T_WILDCARD)
			tmp = pos + ft_strlen(pattern[j]);
	}
	return (ent);
}
